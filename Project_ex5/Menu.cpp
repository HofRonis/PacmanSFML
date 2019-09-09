#include "Menu.h"



Menu::Menu()
{
	m_play_button.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::play_button));
	m_exit_button.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::exit_button));
	m_button_touched.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::button_touched));
	m_winning_menu.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::winning_menu));
}
// manage all the menus
bool Menu::main_loop(sf::RenderWindow & window, sf::Vector2f play_position, sf::Vector2f exit_position)
{
	bool play = false;

	window.create(sf::VideoMode::VideoMode(600, 600), "Pacman");

	while (window.isOpen())
	{
		window.clear();
		
		window.draw(m_menu);
		draw_play_button(window, play_position);
		draw_exit_button(window, exit_position);
		
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{

			case sf::Event::MouseButtonPressed:
				if (Event.mouseButton.button == sf::Mouse::Left) // mouse pressed
				{
					int x = Event.mouseButton.x,
						y = Event.mouseButton.y;
					// if 'play' pressed
					if (x > play_position.x && x < (play_position.x+150) && y>(play_position.y+5) &&
						y < (play_position.y + 75))
					{
						window.close();
						play = true;
					}
					// if 'exit' pressed
					if (x > exit_position.x && x < (exit_position.x+150) && y> (exit_position.y+15) && 
						y < (exit_position.y + 95))
					{
						window.close();
						play = false;
					}
				}
				break;
			case sf::Event::MouseMoved:  // make button sound
				int x = sf::Mouse::getPosition(window).x,
					y = sf::Mouse::getPosition(window).y;
				if (x > play_position.x && x < (play_position.x + 150) && y>(play_position.y + 5) &&
					y < (play_position.y + 75))
				{
					m_button_touched.play();
				}
				if (x > exit_position.x && x < (exit_position.x + 150) && y>(exit_position.y + 15) &&
					y < (exit_position.y + 95))
				{
					m_button_touched.play();
				}
				break;
			
			}
		}
		// move the button- button touched
		int x = sf::Mouse::getPosition(window).x,
			y = sf::Mouse::getPosition(window).y;

		if (x > play_position.x && x < (play_position.x + 150) && y>(play_position.y + 5) &&
			y < (play_position.y + 75))
		{
			draw_play_button(window, { play_position.x - 3, play_position.y + 3 });
		}
		if (x > exit_position.x && x < (exit_position.x + 150) && y>(exit_position.y + 15) &&
			y < (exit_position.y + 95))
		{
			draw_exit_button(window, { exit_position.x - 3, exit_position.y + 3 });
		}
		window.display();

	}
	return play;
}

// start menu
bool Menu::start(sf::RenderWindow & window)
{
	bool play = false;
	m_menu.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::start_menu));
	play = main_loop(window, { 200,220 }, { 450,210 });

	return play;
}

// winning menu
bool Menu::win(sf::RenderWindow & window)
{
	bool play = false;
	m_menu.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::winner));
	m_winning_menu.play();
	m_winning_menu.setLoop(true);
	play = main_loop(window, { 200,350 }, { 450,355 });
	m_winning_menu.stop();
	return play;
}

// lose menu
bool Menu::lose(sf::RenderWindow & window)
{
	bool play = false;
	m_menu.setTexture(ResourceManager::instance().Get_Texture(ResourceManager::game_over));
	play = main_loop(window, { 125,450 }, { 395,440 });

	return play;
}

// draw play button
void Menu::draw_play_button(sf::RenderWindow & window, sf::Vector2f position)
{
	m_play_button.setPosition(position);
	window.draw(m_play_button);
}

// draw exit button
void Menu::draw_exit_button(sf::RenderWindow & window, sf::Vector2f position)
{
	m_exit_button.setPosition(position);
	window.draw(m_exit_button);
}

Menu::~Menu()
{
}

