#include "Pacman.h"


Pacman::Pacman()
{
}

//constructor
Pacman::Pacman( sf::Color color, sf::Vector2f position, char c)
	:Dynamic(color,position ,c){
	// make the origin of the pacan in its center
	m_pic.setOrigin(12.5f, 12.5f);
}

// set pisition
void Pacman::set_position(sf::Vector2f new_position) {
	Object::set_position(new_position + sf::Vector2f(12.5f, 12.5f));
}

//rotate the pacman image
void Pacman::rotate(int rotation)
{
	m_pic.setRotation(rotation);
}

// draw the pacman
void Pacman::draw(sf::RenderWindow & window)
{
	// using sungletone 
	m_pic.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::pacman));
	m_pic.setColor(m_color);
	
	window.draw(m_pic);
}

// move the pacman direction
void Pacman::move(int direction) // 0- up, 1- down, 2- left, 3- right
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

Pacman::~Pacman()
{
}
