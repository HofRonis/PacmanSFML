#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>


class ResourceManager
{
public:


	static ResourceManager & instance();
	const sf::Font & GetFont() const;
	
	

	
	enum Picture_Type {
		pacman,
		wall,
		cookie,
		devil,
		start_menu,
		game_over,
		winner,
		play_button,
		exit_button
	};

	enum Audio_Type {
		game_over_menu,
		winning_menu,
		start_game,
		soundtrack,
		eat_cookie,
		strike,
		button_touched
	};


	const sf::Texture &Get_Texture(Picture_Type character) const;
	const sf::SoundBuffer &Get_Audio(Audio_Type audio) const;


	~ResourceManager();



private:
	
	std::vector <sf::SoundBuffer> m_music;
	std::vector<sf::Texture> m_picture;
	sf::Font m_font;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager();

};

