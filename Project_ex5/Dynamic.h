#pragma once
#include "Object.h"
class Dynamic :public Object
{
public:
	Dynamic(sf::Color color, sf::Vector2f position, char c);
	Dynamic();

	sf::Vector2f get_first_position() const;
	virtual void move(int direction)= 0;
	~Dynamic();

protected:
	sf::Vector2f m_first_position;
};

