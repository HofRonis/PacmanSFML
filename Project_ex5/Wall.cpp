#include "Wall.h"



Wall::Wall( sf::Color color, sf::Vector2f position, char c)
	: Static(color,position,c)
{
}

// draw the image
void Wall::draw(sf::RenderWindow & window)
{
	// use singletone
	m_pic.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::wall));

	m_pic.setPosition(m_position);
	m_pic.setColor(m_color);
	window.draw(m_pic);
}

Wall::~Wall()
{
}
