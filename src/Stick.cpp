#pragma once

#include "Stick.h"
#include "RectChecker.h"
#include <unordered_map>
#include <iostream>

//=================================
//          constructor
//=================================
Stick::Stick()
{
	m_stick.setSize(Random::getSize());
	m_stick.setOrigin(m_stick.getSize() / 2.f); 
	m_stick.setPosition(Random::getCoordinates());
	m_stick.setOutlineThickness(0.f);
	m_stick.setFillColor(Random::getColor());
	m_stick.setRotation(Random::getAngle());
	m_stick.setOutlineThickness(2.f);
	m_stick.setOutlineColor(sf::Color::Black);
}
//=================================
//          constructor
//=================================
Stick::Stick(const sf::RectangleShape& rectangle)
	:  m_stick(rectangle)
{}
//=================================
//          desstructor
//=================================
std::vector<shared_ptr<Stick>> Stick::removeFromUnderAndGetAvailable(shared_ptr<Stick> stick) 
{
	std::vector<shared_ptr<Stick>> liftAvailable;

	for (auto underStick : m_under)
	{
		underStick->m_above.erase(stick);
		
		if (underStick->m_above.size() < 1)
			liftAvailable.push_back(underStick);
	}

	return liftAvailable;
}
//=================================
//           draw func
//=================================
void Stick::draw(sf::RenderWindow& window)
{
	window.draw(m_stick);
}
//=================================
//        add_to_above_map
//=================================
void Stick::addToAboveMap(shared_ptr<Stick> stick)
{
    m_above.insert(stick);
}
//=================================
//        add_to_under_map
//=================================
void Stick::addToUnderMap(shared_ptr<Stick> stick)
{
	m_under.push_back(stick);
}
//=================================
//         == operator
//=================================
bool operator==(shared_ptr<Stick> lhs, shared_ptr<Stick> rhs)
{
	static RectChecker rectChecker;
	return rectChecker.rectanglesIntersect(lhs->m_stick, rhs->m_stick);
}
//=================================
//        can be removed 
//=================================
bool Stick::canBeRemoved()
{
	return m_above.empty();
}
//=================================
//         get stick rect
//=================================
sf::RectangleShape Stick::getStickRect() const
{
	return m_stick;
}
//=================================
//       get whats under
//=================================
std::unordered_set<shared_ptr<Stick>>& Stick::getAbove()
{
	return m_above;
}
//=================================
//       get whats under
//=================================
std::vector<shared_ptr<Stick>> Stick::getUnder()
{
	return m_under;
}
//=================================
//       get color as str
//=================================
std::string Stick::getColorAsStr()
{
	if (m_stick.getFillColor() == sf::Color::Red)
		return "Red";
	else if (m_stick.getFillColor() == sf::Color::Blue)
		return "Blue";
	else if (m_stick.getFillColor() == sf::Color::Yellow)
		return "Yellow";
	else if (m_stick.getFillColor() == sf::Color::Green)
		return "Green";
	else //if color == purple
		return "Purple";
}
//=================================
//         add highlight
//=================================
void Stick::addHighlight()
{
	m_stick.setOutlineColor(sf::Color::White);
	m_stick.setOutlineThickness(5.f);
}
//=================================
//       remove highlight
//=================================
void Stick::removeHighlight()
{
	m_stick.setOutlineThickness(2.f);
	m_stick.setOutlineColor(sf::Color::Black);
}
//=================================
//          get Score
//=================================
int Stick::getPoint()
{
	if (m_stick.getFillColor() == sf::Color::Blue)
		return 9;
	else if (m_stick.getFillColor() == sf::Color::Red)
		return 4;
	else if (m_stick.getFillColor() == sf::Color::Yellow)
		return 2;
	else if (m_stick.getFillColor() == sf::Color::Green)
		return 7;
	else //then the color is purple
		return 5;
}
