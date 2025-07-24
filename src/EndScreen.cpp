#include "EndScreen.h"
#include "Resources.h"


//==========================================
//              constructor
//==========================================
EndScreen::EndScreen()
    :  m_text(Resources::instance().getText())
{}
//==========================================
//            draw score screen
//==========================================
void EndScreen::drawScoreScreen(int score)
{
    m_text.setCharacterSize(50);
    m_text.setString("Total Score: " + std::to_string(score));   
    setTextPos();
    draw();
}
//==========================================
//            draw save screen
//==========================================
void EndScreen::drawSaveScreen()
{
    m_text.setCharacterSize(50);
    m_text.setString("Game Saved Successfully!");
    setTextPos();
    draw();
}
//==========================================
//            draw exit screen
//==========================================
void EndScreen::drawExitScreen()
{
    m_text.setCharacterSize(50);
    m_text.setString("Hope to see you soon!");
    setTextPos();
    draw();
}
//==========================================
//            draw save screen
//==========================================
void EndScreen::drawLostScreen()
{
    m_text.setCharacterSize(50);
    m_text.setString("Nice try maybe next time");
    setTextPos();
    draw();
}
//==========================================
//            set text size
//==========================================
void EndScreen::setTextPos()
{
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setPosition(SCREEN_X / 2.0f, SCREEN_Y / 2.0f);
}
//==========================================
//                  draw
//==========================================
void EndScreen::draw()
{
    m_clock.restart();

    while (m_clock.getElapsedTime().asSeconds() < 2)
    {
        Resources::instance().getWindow().clear();
        Resources::instance().getWindow().draw(m_text);
        Resources::instance().getWindow().display();
    }
}