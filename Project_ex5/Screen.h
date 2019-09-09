#pragma once
#include "Pacman.h"
#include "Stage_Loader.h"
#include "Player_Status.h"
#include "Devil.h"
#include <string.h>
#include <vector>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Static.h"
#include "Search_Algorithm.h"
#include "ResourceManager.h"
#include <typeinfo>
#include <math.h>  


class Screen
{
public:
	Screen();
	bool move_pacman(int prev_direction, int direction,Player_Status * stat, sf::Clock *cookie_clock, bool &collision); // 0- up, 1- down, 2- left, 3- right
	bool wall_collision(sf::Vector2f next_position, int direction, bool pacman, int devil_index);
	void load_level(int level);
	void draw(sf::RenderWindow & window);

	bool pacman_wall_collision(int x, int y);
	sf::Vector2f get_center_of_sprite(sf::Sprite picture);
	double get_radius_of_pacman();

	double distance(sf::Vector2f v1, sf::Vector2f v2);
	bool pacman_cookie_collision(sf::Vector2f next_position, int direction, Player_Status *stat, sf::Clock *cookie_clock);

	bool devil_wall_collision(int x, int y, int devil_index);

	void move_random_devil(int devil_index);
	
	void set_eaten_cookies(int num);

	void move_devils();

	int get_rows_num() const;
	int get_cols_num() const;
	int get_stage_cookies() const;
	int get_eaten_cookies() const;
	int Get_Num_Devils() const;
	bool pacman_devil_collision(sf::Sprite pacman, sf::Sprite devil);
	bool IsValid(sf::Vector2f);
	bool PacmanIsValid(sf::Vector2f);
	
	void rotatePacman(int direction);

	void clear_all();
	~Screen();

	

private:
	std::unique_ptr<Pacman> m_pacman;

	Stage_Loader m_level;
	

	std::vector < std::unique_ptr <Devil> >  m_devil;
	std::vector< std::vector < std::unique_ptr <Static> > > m_static;
	int m_eaten_cookies;

	Search_Algorithm m_algorithm;
	sf::Sound m_eat_cookie_audio;






};

