#include "Object.h"



Object::Object( sf::Color color, sf::Vector2f position, char c)
	: m_color(color),m_position(position),m_type(c){}

Object::Object()
{
}

//return the object picture
const sf::Sprite& Object::get_pic() const
{
	return m_pic;
}

// get the object type
char Object::get_type() const
{
	return m_type;
}

// set the object position
void Object::set_position(sf::Vector2f new_position)
{
	m_position = new_position;
}

// set color to the image
void Object::set_color(sf::Color color)
{
	m_color = color;
}

// get the object position
sf::Vector2f Object::get_position() const
{
	return m_position;
}

Object::~Object()
{
}
