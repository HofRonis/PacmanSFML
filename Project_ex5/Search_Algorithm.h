#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Static.h"


struct Node {
	sf::Vector2i _direction;
	bool discovered;
};

const sf::Vector2i	UP = { 0,1 },
DOWN = { 0,-1 },
LEFT = { -1,0 },
RIGHT = { 1,0 };


class Search_Algorithm
{
public:

	enum direction_type {
		left, right, up, down
	};
	Search_Algorithm();

	int bfs(sf::Vector2i src, sf::Vector2i dst,
		int num_rows, int num_cols, std::vector< std::vector < std::unique_ptr <Static> > > *static_vec);
	~Search_Algorithm();
	bool check_node(sf::Vector2i &vertex, sf::Vector2i direction_1,
		std::vector< std::vector < std::unique_ptr <Static> > > *static_vec,
		std::vector <std::vector <Node> > *map_ptr, int num_rows, int num_cols, int index);

private:

	sf::Vector2i m_source,
		m_destination;
	std::vector <sf::Vector2i> m_que;
	std::vector <sf::Vector2i> m_direction;
	std::vector <direction_type> m_direction_name;
};