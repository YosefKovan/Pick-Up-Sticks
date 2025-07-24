#pragma once

#include <string>
#include <SFML/Graphics.hpp>

const int SCREEN_X = 1200, SCREEN_Y = 700;

enum Colors{Blue, Green, Red, Yellow, Purple };

const int TOTAL_COLORS = 5;

const int MAX_STICK_SIZE = 250, MAX_TOTAL_STICKS = 80;

const int MAX_TIME = 1000;

//===========================================
//             image related
//===========================================

enum Images{Background, HelpButton, SaveButton, ExitButton, MenuBack, New, Load, Quit};

const int TOTAL_IMAGES = 8;

const std::string images[TOTAL_IMAGES] = {"board.jpg", "help.png", "save.png", "exit.png", 
                                          "menu background.jpg", "new.png", "load.png", "quit.png"};

const sf::Vector2f imgSize[TOTAL_IMAGES] = {sf::Vector2f(1200, 700), sf::Vector2f(120,120),
                                            sf::Vector2f(120,120), sf::Vector2f(120,120),
                                            sf::Vector2f(1200, 700), sf::Vector2f(250,120),
                                            sf::Vector2f(250,110), sf::Vector2f(250,100)};

const sf::Vector2f imgLocation[TOTAL_IMAGES] = {sf::Vector2f(0, 0),sf::Vector2f(1050,100),
                                                sf::Vector2f(1050, 300), sf::Vector2f(1050, 490),
                                                sf::Vector2f(0, 0),sf::Vector2f(450, 100),sf::Vector2f(450, 300),
                                                sf::Vector2f(450, 500) };

//===========================================
//             text related
//===========================================

const int TotalText = 5;

enum TopbarText { ScoreTxt, SticksLeftTxt, SticksAvailableTxt, SticksPicked, TimerTxt };

const sf::Vector2f TextLocations[TotalText] = { sf::Vector2f(30,10), sf::Vector2f(230, 10),
                                                sf::Vector2f(550,10), sf::Vector2f(890, 10), sf::Vector2f(500, 650)};

//===========================================
//            menu related
//===========================================

enum MenuReturnValue { close, play, load };

//===========================================
//          File reading related
//===========================================

enum rectXyInfo{size, origin, pos};

enum rectIntInfo{rotation, r, g, b};


