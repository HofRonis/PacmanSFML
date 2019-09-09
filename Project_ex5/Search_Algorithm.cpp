#include "Search_Algorithm.h"



Search_Algorithm::Search_Algorithm()
{
	m_direction = { UP,DOWN,LEFT,RIGHT };
	m_direction_name = { up,down,left,right };
}


int Search_Algorithm::bfs(sf::Vector2i start, sf::Vector2i target,
	int num_rows, int num_cols,
	std::vector< std::vector < std::unique_ptr <Static> > > *static_vec)
{
	bool found_destination = false, //check if we got to the target
		 first = true;

	std::vector <std::vector <Node> > map; // map of the level
	sf::Vector2i save_start = start; // save the source position
	m_destination = target; 
	m_source = start;

	
	if (m_destination == m_source)
		return 5;
	// initialize all the location in the map to not visited
	for (int i = 0; i < num_cols; i++)
	{
		map.push_back({});

		for (int j = 0; j < num_rows; j++)
		{
			map.back().push_back({});
			map[i][j].discovered = false;
		}
	}

	m_que.clear(); 

	m_que.push_back(start); // push the source to the queue

	while (!m_que.empty() && !found_destination)
	{
		save_start = m_que[0];
		sf::Vector2i save_double = m_que[0];
		m_que.erase(m_que.begin());

		// we visiting all the neighbors of the location in the top of the queue(in place -0)
		// the location from his left,right,up and down
		for (int i = 0; i < 4 && !found_destination; i++)
		{
			found_destination = check_node(save_start, m_direction[i], static_vec, &map, num_rows, num_cols, i);

			save_start = save_double;
		}
		map[save_double.y][save_double.x].discovered = true;
	}

	// initialize all the location in the map to not visited for the next time
	for (int i = 0; i < num_cols; i++)
	{
		for (int j = 0; j < num_rows; j++)
		{
			map[i][j].discovered = false;
		}
	}

	if (m_que.size() == 0) // check if we find the target
		return 5;

	sf::Vector2i backwbackwards_vertex = m_que.at(m_que.size() - 1); // store the target position

	direction_type path; // store the direction of the devil

	// check if we got to the source, we do the opposite way from the target to the source
	// and choose the opposite of the last direction
	while ((backwbackwards_vertex != m_source))
	{
		if (map[backwbackwards_vertex.y][backwbackwards_vertex.x]._direction == LEFT)
		{
			backwbackwards_vertex.x -= 1;
			path = left;
		}
		else if (map[backwbackwards_vertex.y][backwbackwards_vertex.x]._direction == RIGHT)
		{
			backwbackwards_vertex.x += 1;
			path = right;

		}
		else if (map[backwbackwards_vertex.y][backwbackwards_vertex.x]._direction == UP)
		{
			backwbackwards_vertex.y -= 1;
			path = up;

		}
		else
		{
			backwbackwards_vertex.y += 1;
			path = down;
		}

		sf::Vector2i devil_path = map[backwbackwards_vertex.y][backwbackwards_vertex.x]._direction;
	}
	if (path == left)
		return 3;
	if (path == right)
		return 2;
	if (path == up)
		return 1;

	return 0;
}
	// in this function we check every neighbor if it wall or visitied, and if it not we pushing him
	// to the queue
bool Search_Algorithm::check_node(sf::Vector2i &vertex, sf::Vector2i direction_1,
	std::vector< std::vector < std::unique_ptr <Static> > > *static_vec,
	std::vector <std::vector <Node> > *map_ptr, int num_rows, int num_cols, int index)
{
	sf::Vector2i stat_vertex = vertex; 
	// check which direction
	for (int i = 0; i< m_direction_name.size(); i++)
		if (m_direction[i] == direction_1)
		{
			switch (m_direction_name[i])
			{
			case left:
				vertex.x = vertex.x - 1;
				break;
			case right:
				vertex.x = vertex.x + 1;
				break;
			case up:
				vertex.y = vertex.y - 1; 					 
				break;
			case down:
				vertex.y = vertex.y + 1;
				break;
			}
		}
	// check if the location is in the map
	if (vertex.y >= num_cols || vertex.y <0 || vertex.x >= num_rows || vertex.x < 0)
		return false;

	if (static_vec->at(vertex.x).at(vertex.y) == nullptr || static_vec->at(vertex.x).at(vertex.y) != nullptr)
	{
		// check if there is an object in this location on the map
		if (static_vec->at(vertex.x).at(vertex.y) != nullptr)
		{
			// check if its wall or if we already visited this location on the map
			if (static_vec->at(vertex.x).at(vertex.y)->get_type() != '#'
				&& static_vec->at(vertex.x).at(vertex.y)->get_type() != 'E'
				&& static_vec->at(vertex.x).at(vertex.y)->get_type() != 'D'
				&& map_ptr->at(vertex.y).at(vertex.x).discovered == false)
			{
				map_ptr->at(vertex.y).at(vertex.x).discovered = true;
				map_ptr->at(vertex.y).at(vertex.x)._direction = direction_1 * -1;

				m_que.push_back(vertex);
				sf::Vector2i opposite = { vertex.y,vertex.x };

				if (m_destination == opposite)
					return true;
			}
		}

		if ((static_vec->at(vertex.x).at(vertex.y) == nullptr))
		{
			// check if we already visited this location on the map
			if (map_ptr->at(vertex.y).at(vertex.x).discovered == false)
			{
				map_ptr->at(vertex.y).at(vertex.x).discovered = true;
				map_ptr->at(vertex.y).at(vertex.x)._direction = direction_1 * -1;
				m_que.push_back(vertex);
				sf::Vector2i opposite = { vertex.y,vertex.x };

				if (m_destination == opposite)
					return true;
			}
		}
	}
	return false;
}



Search_Algorithm::~Search_Algorithm()
{
}



