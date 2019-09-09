#include "Smart_Devil.h"



Smart_Devil::Smart_Devil( sf::Color color, 
						 sf::Vector2f position, char c, bool smart)
	: Devil(color,position,c,smart,5)
{
}
// draw the devil
void Smart_Devil::draw(sf::RenderWindow & window)
{
	// using sungletone 
	m_pic.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::devil));
	m_pic.setColor(m_color);
	window.draw(m_pic);
}

// move the devil direction
void Smart_Devil::move(int direction) // 0- up, 1- down, 2- left, 3- right
{
	switch (direction)
	{
	case 0:
		m_position = { m_position.x  , m_position.y - 1 };
		break;
	case 1:
		m_position = { m_position.x  , m_position.y + 1 };
		break;
	case 2:
		m_position = { m_position.x - 1 , m_position.y };
		break;
	case 3:
		m_position = { m_position.x + 1 , m_position.y };
		break;
	}
	// update the image location
	m_pic.setPosition(m_position);
}

Smart_Devil::~Smart_Devil()
{
}
