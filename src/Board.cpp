#pragma once

#include "Board.h"
#include <iostream>
#include "Resources.h"

//===============================================
//                constructor
//===============================================
Board::Board()
    :  m_gameOver(false) 
{  
    srand(time(NULL));
    createSticks();
    placeUnderAndAbove();
    m_topBar = TopBar(Random::getTime(m_sticks.size()));
    setAvailableSticks(); 
}
//===============================================
//                constructor
//===============================================
Board::Board(const std::list<shared_ptr<Stick>>& sticks, const TopBar& topBar)
    :  m_topBar(topBar), m_sticks(sticks), m_gameOver(false)
{
    placeUnderAndAbove();
    setAvailableSticks();
}
//===============================================
//                play game 
//===============================================
void Board::playGame() {

    Resources::instance().getWindow().create(sf::VideoMode(SCREEN_X, SCREEN_Y), "Game Screen");

    m_topBar.resetClock();

    while (!m_gameOver && m_sticks.size() > 0 && m_topBar.getTimeLeft() > 0)
    {
        m_topBar.updateContainerSizes(m_sticks, m_availablePick);
        draw();
        checkForPlayerClick();
    }

    if (m_sticks.size() == 0)
        m_endScreen.drawScoreScreen(m_topBar.getTotalScore());
    else if (m_topBar.getTimeLeft() <= 0)
        m_endScreen.drawLostScreen();


    Resources::instance().getWindow().close();
}
//===============================================
//            set available sticks 
//===============================================
void Board::setAvailableSticks()
{
    for (auto stick : m_sticks)
        if (stick->canBeRemoved())
            m_availablePick[stick->getColorAsStr()].push_back(stick);
}
//===============================================
//                   draw
//===============================================
void Board::draw()
{
    Resources::instance().getWindow().clear();
    Resources::instance().drawBackground();
    
    //here we draw the sticks
    for (auto m = m_sticks.begin(); m != m_sticks.end(); m++)
         (*m)->draw(Resources::instance().getWindow());

    m_topBar.drawTopBar();
    m_sideBar.drawSideBar();
    Resources::instance().getWindow().display();
}
//===============================================
//            checkForPlayerClick
//===============================================
void Board::checkForPlayerClick()
{
    if (auto event = sf::Event{}; Resources::instance().getWindow().pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            Resources::instance().getWindow().close();
            break;
        case sf::Event::MouseButtonReleased:
            if (clickedStick(event.mouseButton))
                return;
            if (m_sideBar.checkHelpButtonPressed(event.mouseButton))
            {
                drawOneByOneHighlight();
            }
            if (m_sideBar.checkExitButtonPressed(event.mouseButton))
            {
                m_endScreen.drawExitScreen();
                m_gameOver = true;
            }
            if (m_sideBar.checkSaveButtonPressed(event.mouseButton))
            {
                m_fileDealing.saveToFile(m_sticks, m_topBar);
                m_endScreen.drawSaveScreen();
                m_gameOver = true;
            }
        }
    }
}
//===============================================
//              creatte sticks
//===============================================
void Board::createSticks()
{
    int size = Random::getAmount();
    for (int i = 0; i < size; i++)
        m_sticks.push_back(std::make_shared<Stick>());
}
//===============================================
//          place under and above
//===============================================
void Board::placeUnderAndAbove()
{ 
    for (auto it1 = m_sticks.begin(); it1 != m_sticks.end(); it1++)
    {
        for (auto it2 = m_sticks.begin(); it2 != it1; it2++) {
            if ((*it2) == (*it1)) 
            {
                (*it1)->addToUnderMap(*it2);
            }
        }
        for (auto it2 = std::next(it1); it2 != m_sticks.end(); it2++) {
            if ((*it2) == (*it1))
            {
                (*it1)->addToAboveMap(*it2);
            }
        }
    }
}
//===============================================
//               clicked stick
//===============================================
bool Board::clickedStick(const sf::Event::MouseButtonEvent& event)
{
    for (auto it = m_sticks.rbegin(); it != m_sticks.rend(); it++)
    {
        //this will check if the mouse click is within any of the sticks
        if (insideRotatedRectangle((*it)->getStickRect(),
            Resources::instance().getWindow().mapPixelToCoords({ event.x, event.y })))
        {
            if ((*it)->canBeRemoved())
            {
                auto availableSticks = (*it)->removeFromUnderAndGetAvailable(*it);
                //add sticks to the can remove sticks
                updateAvailablePick(availableSticks, *it);
                //here we will increment the total score
                m_topBar.updateScoreAndSticksPickedUp((*it)->getPoint());
                //remove the current pointer from the stick data structure
                m_sticks.erase(std::next(it).base());
            }
            else 
            {
                drawAllAtOnceHighlight((*it)->getAbove());
            }
            return true; 
        }
    }
    
    return false;
}
//===============================================
//           update Available Pick
//===============================================
void Board::updateAvailablePick(vector<shared_ptr<Stick>>& availableSticks, shared_ptr<Stick> stick)
{
    for (auto available : availableSticks)
        m_availablePick[available->getColorAsStr()].push_back(available);
   
    //here we will remove the current stick from the available picks
    auto mapIterator = m_availablePick.find(stick->getColorAsStr());
    auto vecIterator = std::find(mapIterator->second.begin(), mapIterator->second.end(), stick);
    
    if(vecIterator != mapIterator->second.end())
       mapIterator->second.erase(vecIterator);
}
//===============================================
//         draw All At Once Highlight
//===============================================
void Board::drawAllAtOnceHighlight(const std::unordered_set<shared_ptr<Stick>>& aboveSticks)
{
    m_clock.restart();

    for (auto stick : aboveSticks)
         stick->addHighlight();
    
    while (m_clock.getElapsedTime().asSeconds() < 0.8)
          draw();

    for (auto stick : aboveSticks)
        stick->removeHighlight();
}
//===============================================
//          draw One By One Highlight
//===============================================
void Board::drawOneByOneHighlight()
{
    //add highlights and draw each stick one at a time
    for (auto it = m_availablePick.begin(); it != m_availablePick.end(); it++)
    {
        for (auto& stick : it->second)
        {
            stick->addHighlight();
            m_clock.restart();

            while (m_clock.getElapsedTime().asSeconds() < 0.5)
                draw();
        }
    }

    //here we will remove the highlight from the sticks
    for (auto it = m_availablePick.begin(); it != m_availablePick.end(); ++it)
    {
        for (auto& stick : it->second) 
            stick->removeHighlight();
        
    }
}
//===============================================
//           inside Rotated Rectangle
//===============================================
bool Board::insideRotatedRectangle(const sf::RectangleShape& rectangle, const sf::Vector2f& mouseClick)
{
    sf::Transform inverseTransform = rectangle.getInverseTransform();
    sf::Vector2f localPoint = inverseTransform.transformPoint(mouseClick);
    sf::FloatRect localBounds = rectangle.getLocalBounds();
    return localBounds.contains(localPoint);
}
