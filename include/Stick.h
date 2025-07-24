#pragma once 

#include "Random.h"
#include <SFML/Graphics.hpp>
#include <unordered_set>

using std::shared_ptr;
using std::vector;

class Stick {

public:
	Stick();
	Stick(const sf::RectangleShape& rectangle);
	void draw(sf::RenderWindow&);
	void addToAboveMap(std::shared_ptr<Stick>);
	void addToUnderMap(std::shared_ptr<Stick>);
	bool canBeRemoved();
	void addHighlight();
	void removeHighlight();
	int getPoint(); 
	std::string getColorAsStr();
	sf::RectangleShape getStickRect() const;
	std::vector<shared_ptr<Stick>> getUnder();
	std::unordered_set<shared_ptr<Stick>>& getAbove();
	friend bool operator==(shared_ptr<Stick>, shared_ptr<Stick>);
	vector<shared_ptr<Stick>> removeFromUnderAndGetAvailable(shared_ptr<Stick>);

private:
	sf::RectangleShape m_stick;
	std::unordered_set<std::shared_ptr<Stick>> m_above;
	std::vector<std::shared_ptr<Stick>> m_under;
};








