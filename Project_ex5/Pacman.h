#pragma once
#include "Dynamic.h"
#include "ResourceManager.h"
class Pacman:public Dynamic
{
public:
	
	Pacman( sf::Color color, sf::Vector2f position, char c);
	
	Pacman();

	void move(int direction); 
	void draw(sf::RenderWindow & window);

	void set_position(sf::Vector2f new_position);

	void rotate(int rotation);

	~Pacman();

};

