#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif
#include "Controller.h"

int main()
{
	Controller game; // run the game
	game.run();
}