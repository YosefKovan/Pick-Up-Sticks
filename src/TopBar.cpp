#pragma once 

#include "TopBar.h"
#include <iostream>
#include <SFML/Graphics.hpp>

//=====================================
//            constructors
//=====================================
TopBar::TopBar(int totalTimeSeconds, int totalScore, int sticksPickedUp)
	: m_totalTimeSeconds(totalTimeSeconds), m_sticksPickedUp(sticksPickedUp), 
	  m_totalScore(totalScore)
{
	m_timerInitialized = false;
    m_availableSticks = m_seconds = m_minutes = m_totalSticks = 0;

	for (int i = 0; i < TotalText; i++) 
	{
		m_text.push_back(Resources::instance().getText());
		m_text[i].setPosition(TextLocations[i]);
		m_text[i].setFillColor(sf::Color::White);
	}
}
//=====================================
//         get total time
//=====================================
int TopBar::getTimeLeft() const
{
	return m_totalTimeSeconds;
}
//=====================================
//         get total score
//=====================================
int TopBar::getTotalScore() const 
{
	return m_totalScore;
}
//=====================================
//        get sticks picked up
//=====================================
int TopBar::getSticksPickedUp() const
{
	return m_sticksPickedUp;
}
//=====================================
//           print top bar
//=====================================
void TopBar::drawTopBar()
{
	updateText();

	setTimer();

	for (auto& text : m_text)
		Resources::instance().getWindow().draw(text);

}
//=====================================
//           update score
//=====================================
void TopBar::updateScoreAndSticksPickedUp(int point)
{
	m_totalScore += point;
	m_sticksPickedUp++;
}
//=====================================
//           update text
//=====================================
void TopBar::updateText()
{
	m_text[0].setString("Score: " + std::to_string(m_totalScore));
	m_text[1].setString("Sticks Left: " + std::to_string(m_totalSticks));
	m_text[2].setString("Available pick: " + std::to_string(m_availableSticks));
	m_text[3].setString("Sticks Picked : " + std::to_string(m_sticksPickedUp));
}
//=====================================
//      update Container Sizes
//=====================================
void TopBar::updateContainerSizes(const STICK_LIST& sticks, const AVAILABLE_PICK& mapSticks)
{
	m_totalSticks = sticks.size();
	
	int size = 0;
	for (const auto& vect : mapSticks)
		size += vect.second.size();
	
	m_availableSticks = size;
}
//=====================================
//           timer logic
//=====================================
void TopBar::timerLogic() 
{
	if (m_clock.getElapsedTime().asSeconds() >= 1 || !m_timerInitialized) {
		m_clock.restart();
		m_totalTimeSeconds--;
		m_seconds = m_totalTimeSeconds % 60;
		m_minutes = m_totalTimeSeconds / 60;
		m_timerInitialized = true;
	}	
}
//=====================================
//           display timer
//=====================================
void TopBar::setTimer()
{
	getTimeLeft();
	timerLogic();
	std::string m = ((m_minutes < 10) ? "0" : "");
	std::string s = ((m_seconds < 10) ? "0" : "");
	m_text[4].setString("Timer: " + (m + std::to_string(m_minutes) + " : " + s + std::to_string(m_seconds)));	
}
//=====================================
//            reset clock
//=====================================
void TopBar::resetClock()
{
	m_clock.restart();
}