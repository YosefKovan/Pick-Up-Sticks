#pragma once

#include "SideBar.h"
#include "Consts.h"

//======================================
//           draw side bar
//======================================
void SideBar::drawSideBar()
{
	for(int i = Images::HelpButton; i< Images::MenuBack; i++)
		Resources::instance().getWindow().draw(Resources::instance().getSprite(i));
}
//======================================
//        checkExitButtonPressed
//======================================
bool SideBar::checkExitButtonPressed(const sf::Event::MouseButtonEvent& event)
{
	return Resources::instance().getSprite(ExitButton).getGlobalBounds().contains(
		   Resources::instance().getWindow().mapPixelToCoords({ event.x, event.y }));
}
//======================================
//        checkHelpButtonPressed
//======================================
bool SideBar::checkHelpButtonPressed(const sf::Event::MouseButtonEvent& event)
{
	return Resources::instance().getSprite(HelpButton).getGlobalBounds().contains(
		   Resources::instance().getWindow().mapPixelToCoords({ event.x, event.y }));
}
//======================================
//        checkSaveButtonPressed
//======================================
bool SideBar::checkSaveButtonPressed(const sf::Event::MouseButtonEvent& event)
{
	return Resources::instance().getSprite(SaveButton).getGlobalBounds().contains(
		   Resources::instance().getWindow().mapPixelToCoords({ event.x, event.y }));
}