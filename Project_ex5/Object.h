#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Object
{
public:
	Object(sf::Color color, sf::Vector2f position, char c);
	Object();
	virtual void draw(sf::RenderWindow & window) = 0;
	sf::Vector2f get_position() const;
	virtual void set_position(sf::Vector2f new_position);
	void set_color(sf::Color color);
	char get_type() const;
	const sf::Sprite& get_pic() const;


	~Object();

protected:

	sf::Sprite m_pic;
	sf::Vector2f m_position;
	sf::Color m_color;
	char m_type;

};

