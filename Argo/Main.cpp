#pragma once
#include <iostream>
#include <SDL.h>
#include <time.h>
#include "Game.h"

using namespace std;

///<author>Jack Keogh</author>

int main(int argc, char* argv[])
{
	Game * game = new Game;

	srand(time(NULL));

	game->Init();
	game->Run();

	return 0;
}