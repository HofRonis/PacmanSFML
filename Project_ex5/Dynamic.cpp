#include "Dynamic.h"



Dynamic::Dynamic( sf::Color color, sf::Vector2f position, char c)
	:Object(color, position, c), m_first_position(position){}

// first position for restart a level 
sf::Vector2f Dynamic::get_first_position() const
{
	return m_first_position;
}

Dynamic::Dynamic()
{
}
Dynamic::~Dynamic()
{
}
