#pragma once

#include <SFML/Graphics.hpp>


class Random {

public:
	static sf::Vector2f getSize();
	static int getAmount();
	static sf::Vector2f getCoordinates();
	static sf::Color getColor();
	static float getAngle();
	static unsigned int getTime(int);
};