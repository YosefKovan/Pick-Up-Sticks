#pragma once

#include <SFML/System/Clock.hpp>
#include "Resources.h"

class Menu {

public:
	Menu();
	int runMenu();
	void drawMenu();
private:
	sf::RenderWindow& m_window;
	void handleClickMenu(const sf::Event::MouseButtonEvent& event);
	void getMouseEvent(bool = false);
	bool m_play, m_loadFile, m_exit;
};