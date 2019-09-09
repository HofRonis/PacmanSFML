#include "Devil.h"



Devil::Devil( sf::Color color, sf::Vector2f position, char c, bool smart, int direction)
	: Dynamic(color,position,c), m_is_smart(smart), m_devil_direction(direction), m_devil_prev_direction(5)
{
}
// smart or random devil
bool Devil::get_is_smart() const
{
	return m_is_smart;
}
// current devil direction
int Devil::get_devil_direction() const
{
	return m_devil_direction;
}
//previus devil direction
int Devil::get_devil_prev_direction() const
{
	return m_devil_prev_direction;
}
//set currrent direction
void Devil::set_devil_direction(int new_direction)
{
	m_devil_direction = new_direction;
}
//set previus direction
void Devil::set_devil_prev_direction(int new_direction)
{
	m_devil_prev_direction = new_direction;
}

Devil::~Devil()
{
}
