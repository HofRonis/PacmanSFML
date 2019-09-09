#include "Cookie.h"

Cookie::Cookie(sf::Color color, sf::Vector2f position, char c)
	: Static(color,position,c)
{
}

// draw the image
void Cookie::draw(sf::RenderWindow & window)
{
	// use singletone
	m_pic.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::cookie));
	m_pic.setPosition(m_position);
	m_pic.setColor(m_color);
	window.draw(m_pic);
}

Cookie::~Cookie()
{
}
