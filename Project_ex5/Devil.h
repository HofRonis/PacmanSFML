#pragma once
#include "Static.h"
#include "Dynamic.h"

class Devil:public Dynamic
{
public:
	Devil(sf::Color color, sf::Vector2f position, char c,bool smart, int direction);
	bool get_is_smart() const;
	
	void set_devil_direction(int new_direction);
	void set_devil_prev_direction(int new_direction);

	int get_devil_direction() const;
	int get_devil_prev_direction() const;

	~Devil();
protected:
	bool m_is_smart;
	int m_devil_direction,
		m_devil_prev_direction;

};

