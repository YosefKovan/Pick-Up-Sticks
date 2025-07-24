#pragma once

#include "Random.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Consts.h"


//=================================
//           get color
//=================================
sf::Color Random::getColor()
{
	//srand(time(NULL)); this we will do int the beggining of the program
	
	int color = rand() % TOTAL_COLORS;

	switch (color){

	   case Blue:
		   return sf::Color::Blue;
	   case Green:
		   return sf::Color::Green;
	   case Red:
		   return sf::Color::Red;
	   case Yellow:
		   return sf::Color::Yellow;
	   case Purple:
		   return sf::Color(95, 0, 160);
	}
}
//=================================
//         get coordinates
//=================================
sf::Vector2f Random::getCoordinates()
{
	int x = rand() % 400;
	int y = rand() % 350;

	x += 400;
	y += 175;

	return sf::Vector2f(x, y);
}
//=================================
//          get size
//=================================
int Random::getAmount()
{
	int amount = rand() % MAX_TOTAL_STICKS;
	
	//this will be the default amount
	if (amount < 10)
		amount = 10;
	
	return amount;
}
//=================================
//          get Length
//=================================
sf::Vector2f Random::getSize()
{
	int size = rand() % MAX_STICK_SIZE;

	//this will be the default size
	if (size < 50)
		size = 100;

	return sf::Vector2f(10, size);
 }
//=================================
//          get angle
//=================================
float Random::getAngle()
{
	float angle = rand() % 360;
	
	if (angle == 90 || angle == 270)
		angle = angle + 20;
	
	return angle;
}
//=================================
//          get time
//=================================
unsigned int Random::getTime(int totalSticks)
{
	return 2 * totalSticks;
}