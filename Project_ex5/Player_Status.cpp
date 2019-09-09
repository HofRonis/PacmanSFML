#include "Player_Status.h"



Player_Status::Player_Status(int score,int  lives,float basic_speed,float speed, bool speed_cookie, bool slow_cookie):
	m_score(score),m_lives(lives),m_basic_speed(basic_speed),m_speed(speed),m_speed_cookie(speed_cookie),m_slow_cookie(slow_cookie)
{
}
// get user score
int Player_Status::get_score()
{
	return m_score;
}
// set user score
void Player_Status::set_score(int score)
{
	m_score = score;
}
// get user life
int Player_Status::get_lives() 
{
	return m_lives;
}
// set user life
void Player_Status::set_life(int lives)
{
	m_lives = lives;
}
// get pacman speed
float Player_Status::get_speed() {
	return m_speed;
}
// set pacman or devil speed
void Player_Status::set_speed(float speed)
{
	m_speed = speed;
}
//  get cookie speed
bool Player_Status::get_speed_cookie()
{
	return m_speed_cookie;
}
// set cookie speed
void Player_Status::set_speed_cookie(bool activate)
{
	m_speed_cookie = activate;
}
// get cookie slow
bool Player_Status::get_slow_cookie()
{
	return m_slow_cookie;
}
// set cookie slow
void Player_Status::set_slow_cookie(bool activate)
{
	m_slow_cookie = activate;
}
// get basic speed
float Player_Status::get_basic_speed()
{
	return m_basic_speed;
}

Player_Status::~Player_Status()
{
}
