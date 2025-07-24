#include "Resources.h"

//=================================
//         instance func
//=================================
Resources& Resources::instance()
{
	static auto resources = Resources();
	return resources;
}
//=================================
//         constructor
//=================================
Resources::Resources()
{
	setTextures();
	setText();	
}
//=================================
//          getWindow
//=================================
void Resources::setText()
{
	m_font.loadFromFile("top.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(32);
	m_text.setFillColor(sf::Color::White);
}
//=================================
//          getWindow
//=================================
sf::RenderWindow& Resources::getWindow() {

	return m_window;
}
//=================================
//          set textures
//=================================
void Resources::setTextures()
{
	for (int i = 0 ;i < TOTAL_IMAGES; i++)
	{
		sf::Texture texture;
		texture.loadFromFile(images[i]);
		m_textures.push_back(texture);
	}

	for (int i = 0; i < TOTAL_IMAGES; i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_textures[i]);
		setImageSizeAndPos(sprite, i);
		m_sprites.push_back(sprite);
	}
}
//=================================
//           set size
//=================================
void Resources::setImageSizeAndPos(sf::Sprite& sprite, int index)
{
	//here we set the image size
	float scaleX = imgSize[index].x / m_textures[index].getSize().x;
	float scaleY = imgSize[index].y / m_textures[index].getSize().y;

	sprite.setScale(scaleX, scaleY);
	sprite.setPosition(imgLocation[index]);
}
//=================================
//        draw background
//=================================
void Resources::drawBackground()
{
	m_window.draw(m_sprites[0]);
}
//=================================
//          get text
//=================================
sf::Text& Resources::getText()
{
	return m_text;
}
//=================================
//          get sprite
//=================================
void Resources::drawTopBarImages()
{
	for (int i = 1; i < TOTAL_IMAGES; i++)
		m_window.draw(m_sprites[i]);
}
//=================================
//          get sprite
//=================================
sf::Sprite& Resources::getSprite(int index) 
{
	return m_sprites[index];
}