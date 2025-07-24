#pragma once

#include <SFML/Graphics.hpp>
#include "Consts.h"
#include <list>

class Resources {

public:
	static Resources& instance();
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;
	sf::RenderWindow& getWindow();
	void drawBackground();
	sf::Text& getText();
	void drawTopBarImages();
	sf::Sprite& getSprite(int);

private:
	Resources();
	void setTextures();
	void setText();
	void setImageSizeAndPos(sf::Sprite&, int);
	std::vector<sf::Texture> m_textures;
	std::vector<sf::Sprite> m_sprites;
	sf::RenderWindow m_window;
	sf::Text m_text;
	sf::Font m_font;
};


