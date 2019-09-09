#pragma once
class Player_Status
{
public:
	Player_Status(int score, int  lives, float basic_speed,float speed, bool speed_cookie, bool slow_cookie);
	~Player_Status();

	int get_score();
	void set_score(int score);
	int get_lives();
	void set_life(int lives );
	float get_speed();
	void set_speed(float speed);
	bool get_speed_cookie();
	void set_speed_cookie(bool activate);
	bool get_slow_cookie();
	void set_slow_cookie(bool activate);
	float get_basic_speed();


private:
	int m_score,
		 m_lives;
	float m_speed,
		  m_basic_speed;
	bool m_speed_cookie,
		 m_slow_cookie;
	
};

