#pragma once

#include <SFML/Graphics.hpp>
#include "Stick.h"
#include <list>
#include "Resources.h"


#define AVAILABLE_PICK std::map<std::string, std::vector<shared_ptr<Stick>>>
#define STICK_LIST std::list<std::shared_ptr<Stick>>

class TopBar {

public:
	TopBar(int = 0, int = 0, int = 0);
	void updateContainerSizes(const STICK_LIST&, const AVAILABLE_PICK&);
	int getTimeLeft() const;
	int getTotalScore() const;
	int getSticksPickedUp() const;
	void drawTopBar();
	void updateScoreAndSticksPickedUp(int); 
	void updateText();
	void resetClock();
	
private:
	int m_totalSticks, m_availableSticks;
	int m_totalTimeSeconds, m_minutes, m_seconds;
	int m_totalScore, m_sticksPickedUp;
	bool m_timerInitialized;
	std::vector<sf::Text> m_text;
	std::vector<sf::Sprite> m_sprites;
	sf::Clock m_clock;
	void setTimer();
	void timerLogic();
};