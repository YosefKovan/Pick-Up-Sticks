#pragma once

#include <SFML/Graphics.hpp>

class EndScreen {

public:
	EndScreen();
	void drawScoreScreen(int);
	void drawSaveScreen();
	void drawExitScreen();
	void drawLostScreen();

private:
	void draw();
	void setTextPos();
	sf::Text m_text;
	sf::Clock m_clock;
};