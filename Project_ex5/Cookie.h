#pragma once
#include "Static.h"
#include "ResourceManager.h"


class Cookie:public Static
{
public:
	Cookie( sf::Color color, sf::Vector2f position, char c);
	void draw(sf::RenderWindow & window);

	~Cookie();


};

