#pragma once
#include "Object.h"
class Static:public Object
{
public:
	Static(sf::Color color, sf::Vector2f position, char c);
	~Static();
};

