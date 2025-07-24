#pragma once

#include "Resources.h"
#include <SFML/Graphics.hpp>

class SideBar {

public:
	void drawSideBar();
	bool checkExitButtonPressed(const sf::Event::MouseButtonEvent&);
	bool checkHelpButtonPressed(const sf::Event::MouseButtonEvent&);
	bool checkSaveButtonPressed(const sf::Event::MouseButtonEvent&);	
};