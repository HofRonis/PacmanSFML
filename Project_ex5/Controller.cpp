#include "Controller.h"



Controller::Controller()
	:m_current_level(1),m_status(0,3,100,100,false,false) // default values to game status
{}
 //load level in the screen
void Controller::load_level()
{
	m_screen.load_level(m_current_level);   // load level 
	int num_of_rows = m_screen.get_rows_num();
	int num_of_cols = m_screen.get_cols_num();
	m_window.create(sf::VideoMode::VideoMode(num_of_rows * 35, num_of_cols * 35 + 40), "Pacman");
}

// main game function manager
void Controller::run()
{      
	sf::Sound audio_start_game,
		audio_strike,
		audio_sound_track,
		audio_game_over;
				/*audio_winning_menu*/
	// load music
	audio_start_game.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::start_game)); // constructor
	audio_strike.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::strike));
	audio_sound_track.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::soundtrack));
	audio_game_over.setBuffer(ResourceManager::instance().Get_Audio(ResourceManager::game_over_menu));

	audio_sound_track.play();  // play soundtrack
	audio_sound_track.setLoop(true); // loop soundtrack

	bool want_to_play;
	want_to_play = m_menu.start(m_window); // first menu
	
	if (want_to_play)
	{
		load_level();//  load level 1
		audio_start_game.play();
	}

	std::ostringstream s_score,
		s_lives;
	
	sf::Text game_score,
		lives;

	s_score << "Score: " << m_status.get_score();
	s_lives << "Lives: " << m_status.get_lives();

	///////////////////////////////////////
	sf::Clock clock;
	sf::Time stopper;
	sf::Clock cookie_clock;
	float lastSec = 0;
	float lastSec2 = 0;
	float lastSec3 = 0;
	float currentSec = 0;

	int direction = 5;
	int prev_direction = direction;
	//int devil_direction = rand() % 4;
	while (m_window.isOpen()) // main loop
	{
		lives.setCharacterSize(24);   // for status display:
		game_score.setCharacterSize(24);
		lives.setPosition(180, m_screen.get_cols_num() * 35);
		game_score.setPosition(0, m_screen.get_cols_num() * 35);
		game_score.setFont(ResourceManager::instance().GetFont());
		lives.setFont(ResourceManager::instance().GetFont());

		game_score.setString(s_score.str());
		lives.setString(s_lives.str());

		if (m_screen.get_stage_cookies() == m_screen.get_eaten_cookies()) // finish a level
		{
			m_screen.clear_all(); // empty the vectors
			m_current_level++;
			int score = m_status.get_score();
			m_status.set_score(score + (((m_screen.Get_Num_Devils() + 1) * 50)));
			if (m_current_level > 4) // finish the game
			{
				audio_sound_track.stop();
				want_to_play = m_menu.win(m_window); // finish menu
				if (want_to_play)
				{
					audio_sound_track.play();
					
					m_status.set_life(3);
					m_status.set_score(0);
					m_screen.set_eaten_cookies(0);
					m_current_level = 1;
					m_screen.clear_all();
					load_level();   // start new game

					audio_start_game.play(); 
					
					m_status.set_speed(m_status.get_basic_speed());
					direction = 5;
				}
			}
			else // load nect level
			{
				m_screen.clear_all();
				load_level(); // load levels 2, 3....
				audio_start_game.play();
				m_status.set_speed(m_status.get_basic_speed());
			}
			direction = 5;
			m_status.set_speed(m_status.get_basic_speed());
		}

		sf::Event Event;
		while (m_window.pollEvent(Event))
		{
			switch (Event.type)
			{	

			case sf::Event::Resized:
				m_window.setView(sf::View(sf::FloatRect(0, 0, (float)Event.size.width, (float)Event.size.height)));
				break;

			case sf::Event::KeyPressed:   // get direction for pacman
				prev_direction = direction;
				switch (Event.key.code)
				{
				case sf::Keyboard::Up: 
					direction = 0;  // change to const					
					break;
				case sf::Keyboard::Down: 
					direction = 1;
					break;
				case sf::Keyboard::Left: 
					direction = 2;
					break;
				case sf::Keyboard::Right: 
					direction = 3;
					break;
				case sf::Keyboard::Space:
					direction = 5;
				}
				
				break;
			}
			if (Event.type == sf::Event::Closed)
				m_window.close();		
		}

		currentSec = clock.getElapsedTime().asSeconds(); // game clock
		if (currentSec - lastSec2 > (1 / m_status.get_speed()))
		{
			bool collision = false;
			
			if (m_screen.move_pacman(prev_direction, direction, &m_status, &cookie_clock, collision))
				prev_direction = direction;
			if (collision)
			{
				audio_strike.play();
				direction = 5;
			}
			s_score.str("");
			s_lives.str("");
			s_score << "Score: " << m_status.get_score();
			s_lives << "Lives: " << m_status.get_lives();
			game_score.setString(s_score.str());
			lives.setString(s_lives.str());

			stopper = cookie_clock.getElapsedTime();

			if (stopper.asSeconds() >= 14.f && m_status.get_speed_cookie()) // speed for 14 seconds
				m_status.set_speed(m_status.get_basic_speed());
			if (stopper.asSeconds() >= 7.f && m_status.get_slow_cookie()) // slow for 14 seconds
				m_status.set_speed(m_status.get_basic_speed());

			lastSec2 = currentSec;	
		}
		
		currentSec = clock.getElapsedTime().asSeconds();
		int check = m_status.get_basic_speed();
		if (currentSec - lastSec3 > (1 / (m_status.get_basic_speed()-30))) // move devil slower
		{
			m_screen.move_devils();
			lastSec3 = currentSec;
		}
		currentSec = clock.getElapsedTime().asSeconds();
		if (currentSec - lastSec > (1 / (m_status.get_speed() /4)))
		{
			m_window.clear(sf::Color(0, 0, 0, 250));
			
			m_screen.draw(m_window); // print everything 
			m_window.draw(game_score);
			m_window.draw(lives);
			m_window.display();
			lastSec = currentSec;

			
		}
		if (m_status.get_lives() == 0)  // if game over
		{
			audio_game_over.play();  // load game over menu
			audio_sound_track.stop();
			want_to_play = m_menu.lose(m_window);

			if (want_to_play)  // restart game
			{
				audio_sound_track.play();
				m_status.set_life(3);
				m_status.set_score(0);
				m_screen.set_eaten_cookies(0);
				m_current_level = 1;
				audio_start_game.play();
				m_screen.clear_all();
				load_level();
			}
		}
	}
}

Controller::~Controller()
{
}
