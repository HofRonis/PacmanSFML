#pragma once
#include "Static.h"
#include "ResourceManager.h"

class Wall:public Static
{
public:
	Wall( sf::Color color, sf::Vector2f position, char c);
	void draw(sf::RenderWindow & window);

	~Wall();
};

