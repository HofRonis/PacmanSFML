#pragma once
#include "Menu.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>


#include <iostream> 
#include<SFML/System.hpp>
#include <cassert>
#include <fstream>
#include <math.h>
#include <string>
#include <random>
#include <time.h>
#include<sstream>
#include "ResourceManager.h"
#include "Player_Status.h"



class Controller
{
public:
	Controller();
	void run();
	void load_level();
	~Controller();

private:
	float m_factor;
	Menu m_menu;
	Screen m_screen;
	sf::RenderWindow m_window;
	int m_current_level;
	Player_Status m_status;

};

