#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <list>
#include "Stick.h"
#include "Random.h"
#include "Consts.h"
#include <map>
#include "Menu.h"
#include "TopBar.h"
#include "FileDealing.h"
#include "SideBar.h"
#include "EndScreen.h"

using std::shared_ptr;
using std::vector;
using std::string;
using std::list;
using std::map;
using std::unordered_set;


class Board {

public:
	Board();
	Board(const list<shared_ptr<Stick>>& sticks, const TopBar& topBar);
	void playGame();
	
private:
	void draw();
	void createSticks();
	void placeUnderAndAbove();
	void checkForPlayerClick();
	void drawOneByOneHighlight();
	void setAvailableSticks();
	bool clickedStick(const sf::Event::MouseButtonEvent& event);
	bool insideRotatedRectangle(const sf::RectangleShape&, const sf::Vector2f&);
	void updateAvailablePick(vector<shared_ptr<Stick>>&, shared_ptr<Stick>);
	void drawAllAtOnceHighlight(const unordered_set<shared_ptr<Stick>>&);

	bool m_gameOver;
	sf::Clock m_clock;
	list<shared_ptr<Stick>> m_sticks;
	TopBar m_topBar;
	SideBar m_sideBar;
	FileDealing m_fileDealing;
	EndScreen m_endScreen;
	map<string, vector<shared_ptr<Stick>>> m_availablePick;
};
