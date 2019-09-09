#include "Screen.h"



Screen::Screen()
	:m_eaten_cookies(0)
{
}

// eaten cookies in a level
void Screen::set_eaten_cookies(int num)
{
	m_eaten_cookies = num; 
}
// rotate the pacman texture
void Screen::rotatePacman(int direction)
{
	switch (direction)
	{
	case 0:
		m_pacman->rotate(270); // rotate up
		break;
	case 1:
		m_pacman->rotate(90); // rotate down
		break;
	case 2:
		m_pacman->rotate(180); // rotate left
		break;
	case 3:
		m_pacman->rotate(0); // rotate right
		break;
	}
}
// num of cookies in a level
int Screen::get_stage_cookies() const
{
	return m_level.get_num_cookies(); 
}

// eaten cookies in a level
int Screen::get_eaten_cookies() const
{
	return m_eaten_cookies;  
}

// num of rows in the map
int Screen::get_rows_num() const
{
	return m_level.get_rows_num(); //num of rows
}

// num of cols in the map
int Screen::get_cols_num() const
{
	return m_level.get_cols_num(); //num of cols
}

// make the level name and send it to stage loader
void Screen::load_level(int level)
{
	m_eaten_cookies = 0;     
	std::string level_name = "level" + std::to_string(level) + ".txt";
	m_level.load_level(level_name, m_pacman, &m_static, &m_devil);
}

// check collision betweeb pacman and cookie
bool Screen::pacman_cookie_collision(sf::Vector2f next_position, int direction, Player_Status * stat, sf::Clock *cookie_clock)
{
	unsigned int x = (next_position.x) / 35,
		y = (next_position.y) / 35;
	int width = m_level.get_cols_num(),
		height = m_level.get_rows_num();

	if (m_static[x][y] != nullptr)
	{
		char type = m_static[x][y]->get_type();
		if (type == '*' || type == 'I' || type == 'K') // if cookie is found
		{
			sf::Vector2f v1 = get_center_of_sprite(m_static[x][y]->get_pic());
			sf::Vector2f v2 = m_pacman->get_pic().getPosition();
			if (distance(v1, v2) < (get_radius_of_pacman()) / 2) // if 'on' the cookie
			{
				m_static[x][y] = nullptr;
				if (type == 'I') //speed cookie
				{
					cookie_clock->restart();
					stat->set_speed_cookie(true);
					stat->set_speed(stat->get_speed() + (stat->get_speed()*0.2));
				}
				if (type == '*') // slow cookie
				{
					cookie_clock->restart();
					stat->set_slow_cookie(true);
					stat->set_speed(stat->get_speed() - (stat->get_speed()*0.1));
				}
				return true;
			}
		}
	}
	return false;
}
// distance between two points
double Screen::distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::sqrt(std::pow((v1.x - v2.x), 2)
		+ std::pow((v1.y - v2.y), 2));
}

//check collision between pacman and wall
bool Screen::pacman_wall_collision(int x, int y)
{
	if (m_static[x][y]->get_pic().getGlobalBounds().intersects(m_pacman->get_pic().getGlobalBounds()) ||
		m_pacman->get_pic().getGlobalBounds().intersects(m_static[x][y]->get_pic().getGlobalBounds()))
		return true;

	return false;
}

//check collision between devil and wall
bool Screen::devil_wall_collision(int x, int y, int devil_index)
{
	sf::Vector2f m = m_static[x][y]->get_position();
			float	w = m_static[x][y]->get_pic().getGlobalBounds().width,
					l= m_static[x][y]->get_pic().getGlobalBounds().left,
					t= m_static[x][y]->get_pic().getGlobalBounds().top,
					h= m_static[x][y]->get_pic().getGlobalBounds().height;

			if (w == 0 && l == 0 && t == 0 && h == 0)
				return true;

	if (m_static[x][y]->get_pic().getGlobalBounds().intersects(m_devil[devil_index]->get_pic().getGlobalBounds()) ||
		m_devil[devil_index]->get_pic().getGlobalBounds().intersects(m_static[x][y]->get_pic().getGlobalBounds()))
		return true;

	return false;
}

// check if devil is in range
bool Screen::IsValid(sf::Vector2f point) 
{
	if (point.x <10 || point.y <10 ||
		(point.x >= (35 * (m_level.get_rows_num() - 1) )) ||
		(point.y >= (35 * (m_level.get_cols_num() - 1) )))
		return false;

	return true;
}

// check if pacman is in range
bool Screen::PacmanIsValid(sf::Vector2f point)
{
	if ( point.x <10 || point.y <10 ||
		(point.x >= (35* (m_level.get_rows_num()-1) + 12.5)) ||
		(point.y >= (35 * (m_level.get_cols_num()-1) + 12.5)))
		return false;

	return true;
}

// check wall colision with wall
bool Screen::wall_collision(sf::Vector2f next_position, int direction, bool pacman, int devil_index) // bool pacman or devil
{
		unsigned int x = (next_position.x) / 35,
			y = (next_position.y) / 35;
		if (direction == 1) //up
			y++;
		if (direction == 3) // right
			x++;

		int width = m_level.get_cols_num(),
			height = m_level.get_rows_num();
		// run on 3 down squares
		for (int i = x - 1; i <= x + 1 && i != -1 && i != height; i++)
		{
			if (y <= width - 1 && m_static[i][y] != nullptr)
			{
				char type = m_static[i][y]->get_type();
				if (type == '#' || type == 'E' || type == 'D')
					if (pacman)
					{
						if (pacman_wall_collision(i, y))
							return true;
					}
					else // if devil
						if (devil_wall_collision(i, y, devil_index))
							return true;
			}
		}
		// run on 3 right squares
		for (int i = y - 1; i <= y + 1 && i != -1 && i != width; i++)
		{
			if (x<=height-1 &&  m_static[x][i] != nullptr )
			{
				char type = m_static[x][i]->get_type();
				if (type == '#' || type == 'E' || type == 'D')
				{
					if (pacman)
					{
						if (pacman_wall_collision(x, i))
							return true;
					}
					else // if devil
						if (devil_wall_collision(x, i, devil_index))
							return true;
				}
			}
		}
	return false;
}

// move the pacman
bool Screen::move_pacman(int prev_direction, int direction, Player_Status * stat, sf::Clock *cookie_clock, bool &collision) // 0- up, 1- down, 2- left, 3- right
{
	bool user_direction = false;
	sf::Vector2f prev_pos = m_pacman->get_position();

	m_pacman->move(direction);
	// if wall collision 
	if (!PacmanIsValid(m_pacman->get_position()) || wall_collision(sf::Vector2f(m_pacman->get_pic().getGlobalBounds().left, m_pacman->get_pic().getGlobalBounds().top), direction, true, 0))
	{
		m_pacman->set_position(prev_pos - sf::Vector2f(12.5f, 12.5f));
		if (prev_direction != direction)
		{
			m_pacman->move(prev_direction);
			
				if (!PacmanIsValid(m_pacman->get_position()) || wall_collision(sf::Vector2f(m_pacman->get_pic().getGlobalBounds().left, m_pacman->get_pic().getGlobalBounds().top), prev_direction, true, 0))
					m_pacman->set_position(prev_pos - sf::Vector2f(12.5f, 12.5f));
			
		}

	}
	else
	{
		rotatePacman(direction);
		user_direction = true;
	}
	// check collision with cookie
	if (pacman_cookie_collision(sf::Vector2f(m_pacman->get_pic().getGlobalBounds().left, m_pacman->get_pic().getGlobalBounds().top), direction, stat, cookie_clock))
	{
		m_eaten_cookies++;
		int score = stat->get_score();
		stat->set_score(score + ((m_devil.size() + 1) * 2));
		m_eat_cookie_audio.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::eat_cookie));
		m_eat_cookie_audio.play();
	}
	for (int i = 0; i < m_devil.size(); i++) // check collision with devils
	{
		if (m_devil[i] != nullptr)
			if (pacman_devil_collision(m_pacman->get_pic(), m_devil[i]->get_pic()))
			{
				m_pacman->set_position(m_pacman->get_first_position());
				for (int j = 0; j < m_devil.size(); j++)
				{
					m_devil[j]->set_position(m_devil[j]->get_first_position());
				}
				m_devil[i]->set_position(m_devil[i]->get_first_position());
				stat->set_life(stat->get_lives() - 1);
				collision = true;
				m_pacman->rotate(0);
			}
	}

	return user_direction;
}

// move the devils
void Screen::move_devils()
{
	for (int i = 0; i < m_devil.size(); i++)
	{
		if (!m_devil[i]->get_is_smart()) // if not smart
			move_random_devil(i); 
		else
		{
			int devil_x = m_devil[i]->get_position().x / 35,
				devil_y = m_devil[i]->get_position().y / 35;

			int pacman_x = m_pacman->get_position().x / 35,
				pacman_y = m_pacman->get_position().y / 35;
			// make the bfs path
			m_devil[i]->set_devil_direction(m_algorithm.bfs({ devil_x, devil_y }, { pacman_y ,pacman_x },
				m_level.get_rows_num(), m_level.get_cols_num(), &m_static));
			// bfs corections
			if (m_devil[i]->get_devil_direction() == 5)
				m_devil[i]->set_devil_direction(m_devil[i]->get_devil_prev_direction());

			sf::Vector2f prev_pos = m_devil[i]->get_position();
			m_devil[i]->move(m_devil[i]->get_devil_direction());   //polymorphyzm move
			if (wall_collision(m_devil[i]->get_position(), m_devil[i]->get_devil_direction(), false, i))
			{  // bfs corections
				m_devil[i]->set_position(prev_pos);
				if (m_devil[i]->get_devil_direction() == m_devil[i]->get_devil_prev_direction())
				{
					// bfs corections
					if (m_devil[i]->get_devil_direction() == 1 || m_devil[i]->get_devil_direction() == 0)
						m_devil[i]->set_devil_prev_direction(2);
					if (m_devil[i]->get_devil_direction() == 2 || m_devil[i]->get_devil_direction() == 3)
						m_devil[i]->set_devil_prev_direction(1);
				}
				prev_pos = m_devil[i]->get_position();
				m_devil[i]->move(m_devil[i]->get_devil_prev_direction());
				if (wall_collision(m_devil[i]->get_position(), m_devil[i]->get_devil_prev_direction(), false, i))
				{  // bfs corections
					m_devil[i]->set_position(prev_pos);
					m_devil[i]->set_devil_direction(m_devil[i]->get_devil_prev_direction());
				}
			}
			else
				if (m_devil[i]->get_devil_direction() != 5)
					m_devil[i]->set_devil_prev_direction(m_devil[i]->get_devil_direction());
		}
	}

}
// move random devil
void Screen::move_random_devil(int devil_index)
{
	if (m_devil[devil_index] != nullptr)
	{
		sf::Vector2f prev_pos = m_devil[devil_index]->get_position();

		int x= m_devil[devil_index]->get_position().x/35,
			y= m_devil[devil_index]->get_position().y/35;
		m_devil[devil_index]->move(m_devil[devil_index]->get_devil_direction());
		if (wall_collision(m_devil[devil_index]->get_position(), m_devil[devil_index]->get_devil_direction(),
			false, devil_index) || !IsValid(m_devil[devil_index]->get_position()))
		{
			m_devil[devil_index]->set_position(prev_pos);
			m_devil[devil_index]->set_devil_direction(rand() % 4);
		}
	}

}
// pacman and devil collision
bool Screen::pacman_devil_collision(sf::Sprite pacman, sf::Sprite devil)
{
	if (pacman.getGlobalBounds().intersects(devil.getGlobalBounds()) ||
		devil.getGlobalBounds().intersects(pacman.getGlobalBounds()))
		return true;

	return false;
}
// draw everything
void Screen::draw(sf::RenderWindow & window)
{
	for (unsigned int i = 0; i < m_static.size(); i++)
		for (unsigned int j = 0; j < m_static[0].size(); j++)
			if (m_static[i][j] != nullptr)
				m_static[i][j]->draw(window); // polymorphy draw

	m_pacman->draw(window);

	for (unsigned int i = 0; i < m_devil.size()&& m_devil.size()>0; i++)
		if (m_devil[i] != nullptr)
			m_devil[i]->draw(window); // polymorphy draw
}
// center of the stracture
sf::Vector2f Screen::get_center_of_sprite(sf::Sprite picture)
{
	sf::Vector2f center;
	center.x = picture.getPosition().x + picture.getGlobalBounds().width / 2;
	center.y = picture.getPosition().y + picture.getGlobalBounds().width / 2;
	return center;
}
// radius of pacman
double Screen::get_radius_of_pacman()
{
	double width = m_pacman->get_pic().getGlobalBounds().width;
	return width;
}

// clear all vectors
void Screen::clear_all()
{
	for (int i = 0; i< m_static.size(); i++)
		for (int j = 0; j< m_static[0].size(); j++)
			m_static[i][j] = nullptr;
	for (int i = 0; i < m_devil.size(); i++)
		m_devil[i] = nullptr;

	m_devil.resize(0);

	m_pacman.reset();
}
// num of devils in a level
int Screen::Get_Num_Devils() const
{
	return m_devil.size();
}

Screen::~Screen()
{
}