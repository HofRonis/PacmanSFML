#include "Stage_Loader.h"


Stage_Loader::Stage_Loader()
	:m_stage_coockie_num(0)
{
}
// num of rows in the map
int Stage_Loader::get_rows_num() const
{
	return m_rows;
}

//num of cols in the map
int Stage_Loader::get_cols_num() const
{
	return m_cols;
}

// load the vectors from the file
void Stage_Loader::load_level(std::string level_name, std::unique_ptr <Pacman> &pac,
	std::vector< std::vector < std::unique_ptr <Static> > > *static_vec,
	std::vector < std::unique_ptr <Devil> > *devil_vec)
{
	m_stage_coockie_num = 0;
	std::ifstream levelfile;
	int x, y;
	levelfile.open(level_name);

	char current;
	if (levelfile.is_open())
	{
		
		levelfile >> x >> y;
		levelfile.get(current); // for the first '\n'
	}
	
	m_rows = y;
	m_cols = x;

	
		static_vec->resize(y);
		for (int i = 0; i < y; ++i)
			static_vec->at(i).resize(x);

	int smart_devil_counter = 0; // counter because of the bfs 

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			levelfile.get(current);
			if (current != ' ' && current != '\n')
			{
				if (current == '@' || current == 'W' || current == 'S') // pacman
					update_pacman(pac, current, j, i);
				else
					if (current == '%' || current == 'T' || current == 'G') // devil
						insert_to_dynamic(devil_vec, current,j, i, smart_devil_counter); 
					else												// wall/cookie
						insert_to_static(static_vec, current, j, i); 
					
			}

		}
		levelfile.get(current); // for the '\n'
	}
	levelfile.close();

}

// case of adding pacman object
void Stage_Loader::update_pacman(std::unique_ptr <Pacman> &pacman, char type, int x, int y)
{
	sf::Vector2f fixed_location((x * 35.f) + 5.f, (y * 35.f) + 5.f);
	sf::Color color;
	switch (type)
	{
	case '@':
		color = sf::Color::Red;
		break;
	case 'W':
		color = sf::Color::Green;
		break;
	case 'S':
		color = sf::Color::Blue;
		break;

	}
	pacman = std::make_unique <Pacman>(color, fixed_location, type); // make the pacman
	pacman->set_position(fixed_location);
	pacman->set_color(color);
}

// insert a devil to devil vector
void Stage_Loader::insert_to_dynamic(std::vector < std::unique_ptr <Devil> > *devil_vec, char type,
	int x, int y, int &counter)
{
	sf::Vector2f fixed_location(x * 35.f, y * 35.f);
	sf::Color color;
	switch (type)
	{
	case '%':
		color = sf::Color::Red;
		break;
	case 'T':
		color = sf::Color::Green;
		break;
	case 'G':
		color = sf::Color::Blue;
		break;

	}
	
	int random = rand() % 2;
		
	if (random == 0 && counter<2) // not creating more than 2 smart devil
	{
		devil_vec->push_back(std::make_unique<Smart_Devil>(color, fixed_location, type, true));
		counter++;
	}
	else // create random devil
		devil_vec->push_back(std::make_unique<Random_Devil>(color, fixed_location,type,false));
}

// insert a wall or a cookie to the static vector
void Stage_Loader::insert_to_static(std::vector< std::vector < std::unique_ptr <Static> > > *static_vec, char type, int x, int y)
{
	sf::Vector2f fixed_location(x * 35.f, y * 35.f);
	sf::Color color;
	switch (type)
	{
		// cookie
	case '*':
		color = sf::Color::Red;
		break;
	case 'I':
		color = sf::Color::Green;
		break;
	case 'K':
		color = sf::Color::Blue;
		break;

		// wall
	case '#':
		color = sf::Color::Red;
		break;
	case 'E':
		color = sf::Color::Green;
		break;
	case 'D':
		color = sf::Color::Blue;
		break;
	}

	if (type == '*' || type == 'I' || type == 'K') // make a cookie
	{
		m_stage_coockie_num++;
		static_vec->at(x).at(y) = std::make_unique<Cookie>(color, fixed_location, type);
	}
	if (type == '#' || type == 'E' || type == 'D') // make a wall
		static_vec->at(x).at(y)= std::make_unique<Wall>(color, fixed_location,type); // need to add the type!

}

// num of cookies in a level
int Stage_Loader::get_num_cookies() const
{
	return m_stage_coockie_num;
}

Stage_Loader::~Stage_Loader()
{
}
