#pragma once 

#include "Stick.h"
#include "TopBar.h"
#include <vector>
#include <string>
#include <fstream>
#include<iostream>
#include <sstream>

using std::to_string;
using std::vector;

#define Pair std::pair<std::list<std::shared_ptr<Stick>>, TopBar>

class FileDealing {

public:
	FileDealing() = default;
	void saveToFile(const std::list<std::shared_ptr<Stick>>& sticks, const TopBar&);
	Pair loadFile();
	
private:
	void setAndAddRectangle(const vector<sf::Vector2f>& rectXyInfo, const vector<int>& rectIntInfo);
	void getSticksInfo(const std::list<std::shared_ptr<Stick>>&);
	void getTopBarInfo(const TopBar& topBar);
	void validateTopBar(const std::string&);
	void validateStick(const std::string&);
	void validateData(const vector<sf::Vector2f>&, const vector<int>&) const;
	std::string getRectInfo(std::shared_ptr<Stick> stick);
	std::vector<std::string> m_fileRows;	
	std::list<std::shared_ptr<Stick>> m_sticks;
	TopBar m_topBar;
};

