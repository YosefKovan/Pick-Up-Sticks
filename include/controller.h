#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menu.h"
#include "Resources.h"
#include "Consts.h"


class Controller {

public:
	Controller();
	void gameController();

private:
	void loadGame();
	void newGame();
	Menu m_menu;
	bool m_running;
};