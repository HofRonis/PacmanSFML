#include "Random_Devil.h"



Random_Devil::Random_Devil( sf::Color color, 
						   sf::Vector2f position, char c, bool smart)
	: Devil(color,position,c,smart,2) 
{
}

// draw the devil
void Random_Devil::draw(sf::RenderWindow & window)
{
	// using sungletone 
	m_pic.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::devil));

	//m_pic.setPosition(m_position);
	m_pic.setColor(m_color);
	window.draw(m_pic);
}

// move the devil direction
void Random_Devil::move(int direction) // 0- up, 1- down, 2- left, 3- right
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


Random_Devil::~Random_Devil()
{
}
