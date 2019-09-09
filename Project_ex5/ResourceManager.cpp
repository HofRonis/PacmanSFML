#include "ResourceManager.h"

// constructor
ResourceManager::ResourceManager()
{
	sf::Texture ptr_pacman;
	sf::Texture ptr_wall;
	sf::Texture ptr_cookie;
	sf::Texture ptr_devil;
	sf::Texture start_menu,
		game_over,
		winner,
		play_button,
		exit_button;
										// all the pictures are loaded
	if (!ptr_pacman.loadFromFile("pacman.png"))
		std::cout << "error cannot open picture" << std::endl;
	if (!ptr_wall.loadFromFile("wall.png"))
		std::cout << "error cannot open picture" << std::endl;
	if (!ptr_cookie.loadFromFile("cookie.png"))
		std::cout << "error cannot open picture" << std::endl;
	if (!ptr_devil.loadFromFile("devil.png"))
		std::cout << "error cannot open picture" << std::endl; 

	if (!m_font.loadFromFile("david.ttf"))
		std::cout << "cannot load font";


	if (!start_menu.loadFromFile("start_menu.jpg"))
		std::cout << "cannot load font";
	if (!game_over.loadFromFile("game_over.jpg"))
		std::cout << "cannot load font";
	if (!winner.loadFromFile("winner.jpg"))
		std::cout << "cannot load font";

	if (!play_button.loadFromFile("play_button.png"))
		std::cout << "cannot load font";
	if (!exit_button.loadFromFile("exit_button.png"))
		std::cout << "cannot load font";
	
						// put all the pictures in a vector
	m_picture.push_back(ptr_pacman); //0
	m_picture.push_back(ptr_wall); //1
	m_picture.push_back(ptr_cookie); //2
	m_picture.push_back(ptr_devil); //3
	m_picture.push_back(start_menu); //4
	m_picture.push_back(game_over); //5
	m_picture.push_back(winner); //6
	m_picture.push_back(play_button); //7
	m_picture.push_back(exit_button); //8

	sf::SoundBuffer open_menu,
					game_over_menu,
					winning_menu,
					start_game,
					soundtrack,
					level_success,
					eat_cookie,
					strike,
					button_touched;


								// all the sound files are loaded
	if (!start_game.loadFromFile("start_game.ogg"))
		std::cout << "cannot find audio";
	if (!eat_cookie.loadFromFile("eat_cookie.ogg"))
		std::cout << "cannot find audio";
	if (!strike.loadFromFile("strike.ogg"))
		std::cout << "cannot find audio";
	if (!winning_menu.loadFromFile("winning_menu.ogg"))
		std::cout << "cannot find audio";
	if (!button_touched.loadFromFile("button_touched.ogg"))
		std::cout << "cannot find audio";
	if (!soundtrack.loadFromFile("soundtrack.ogg"))
		std::cout << "cannot find audio";
	if (!game_over_menu.loadFromFile("game_over.ogg"))
		std::cout << "cannot find audio";

							// put all the sound files in a vector
	m_music.push_back(game_over_menu);
	m_music.push_back(winning_menu);
	m_music.push_back(start_game);
	m_music.push_back(soundtrack);
	m_music.push_back(eat_cookie);
	m_music.push_back(strike);
	m_music.push_back(button_touched);
}


ResourceManager & ResourceManager::instance()
{
	static ResourceManager m_instance;
	return m_instance;
}

// get the font
const sf::Font & ResourceManager::GetFont() const
{
	return m_font;
}

// get the picture, using ENUM
const sf::Texture & ResourceManager::Get_Texture(Picture_Type character) const
{
	switch (character)
	{
	case ResourceManager::pacman:
		return  m_picture[0];
		break;
	case ResourceManager::wall:
		return  m_picture[1];
		break;
	case ResourceManager::cookie:
		return  m_picture[2];
		break;
	case ResourceManager::devil:
		return  m_picture[3];
		break;
	case ResourceManager::start_menu:
		return  m_picture[4];
		break;
	case ResourceManager::game_over:
		return  m_picture[5];
		break;
	case ResourceManager::winner:
		return  m_picture[6];
		break;
	case ResourceManager::play_button:
		return  m_picture[7];
		break;
	}
	return  m_picture[8];
}

// get the sound, using ENUM
const sf::SoundBuffer &ResourceManager::Get_Audio(Audio_Type audio) const
{
	switch (audio)
	{
	case ResourceManager::game_over_menu:
		return m_music[0];
		break;
	case ResourceManager::winning_menu:
		return m_music[1];
		break;
	case ResourceManager::start_game:
		return m_music[2];
		break;
	case ResourceManager::soundtrack:
		return m_music[3];
		break;
	case ResourceManager::eat_cookie:
		return m_music[4];
		break;
	case ResourceManager::strike:
		return m_music[5];
		break;
	}
	
	return m_music[6]; // button touched
}

ResourceManager::~ResourceManager()
{
}
