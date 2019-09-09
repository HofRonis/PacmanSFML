#pragma once
#include "Devil.h"
#include "ResourceManager.h"

class Random_Devil:public Devil
{
public:
	Random_Devil( sf::Color color, sf::Vector2f position, char c, bool smart);
	void draw(sf::RenderWindow & window);
	void move(int direction);
	~Random_Devil();
};

