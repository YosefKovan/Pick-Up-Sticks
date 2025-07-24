
#include "Menu.h"
#include "Board.h"



Menu::Menu()
    : m_window(Resources::instance().getWindow()), 
      m_play(false), m_exit(false), m_loadFile(false)
{}
//------------------------------------
int Menu::runMenu() {
    
    m_play = m_exit = m_loadFile = false;
    
    m_window.create(sf::VideoMode(SCREEN_X, SCREEN_Y), "Menu");

    while (true) {
        
        Resources::instance().getWindow().clear();
        
        getMouseEvent(true);

        if (m_exit || !Resources::instance().getWindow().isOpen()) {
            return MenuReturnValue::close;
        }
        if (m_play) {
            return MenuReturnValue::play;
        }
        if (m_loadFile)
            return MenuReturnValue::load;

        drawMenu();
        Resources::instance().getWindow().display();
    }
}

//------------------------------------
void Menu::getMouseEvent(bool menu) {
    
    if (auto event = sf::Event{}; m_window.pollEvent(event)) 
    {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::MouseButtonReleased:
            handleClickMenu(event.mouseButton);
            break;
        }
    }
}

//---------------------------------
void Menu::handleClickMenu(const sf::Event::MouseButtonEvent & event) 
{
    sf::Vector2f eventPos = m_window.mapPixelToCoords({ event.x, event.y });

    if (Resources::instance().getSprite(New).getGlobalBounds().contains(eventPos)) {
        m_play = true;
    }
    else if (Resources::instance().getSprite(Quit).getGlobalBounds().contains(eventPos)) {
        m_exit = true;
    }
    else if (Resources::instance().getSprite(Load).getGlobalBounds().contains(eventPos)) {
        m_loadFile = true;
    }
}
//---------------------------------
void Menu::drawMenu() {
    
    // Drawing the background and buttons
    m_window.draw(Resources::instance().getSprite(MenuBack));
    m_window.draw(Resources::instance().getSprite(New));
    m_window.draw(Resources::instance().getSprite(Load));
    m_window.draw(Resources::instance().getSprite(Quit));
}