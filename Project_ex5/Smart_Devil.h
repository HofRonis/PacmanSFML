#pragma once
#include "Devil.h"
#include "ResourceManager.h"

class Smart_Devil:public Devil
{
public:
	Smart_Devil( sf::Color color, sf::Vector2f position, char c, bool smart);
	
	void move(int direction);
	void draw(sf::RenderWindow & window);
	~Smart_Devil();

};

