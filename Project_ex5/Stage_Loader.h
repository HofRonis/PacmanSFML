#pragma once
//#include "Screen.h"
#include "Pacman.h"
#include <vector>
#include <memory>
//#include "Dynamic.h"
#include "Devil.h"
#include "Static.h"
#include "Object.h"
#include "Cookie.h"
#include "Wall.h"
#include "Smart_Devil.h"
#include "Random_Devil.h"

#include "iostream"

#include <fstream>

class Stage_Loader
{
public:
	Stage_Loader();
	void load_level(std::string level_name, std::unique_ptr <Pacman> &pac,
		std::vector< std::vector < std::unique_ptr <Static> > > *static_vec,
		std::vector < std::unique_ptr <Devil> >  *devil_vec);
	
	void update_pacman(std::unique_ptr <Pacman> &pac, char type, int x, int y);
	void insert_to_dynamic(std::vector < std::unique_ptr <Devil> >  *devil_vec, char type, int x, int y, int &counter);
	void insert_to_static(std::vector< std::vector < std::unique_ptr <Static> > > *static_vec, char type, int x, int y);

	int get_num_cookies() const;
	int get_rows_num() const;
	int get_cols_num() const;

	~Stage_Loader();

private:
	int m_stage_coockie_num,
		m_rows,
		m_cols;
	
};

