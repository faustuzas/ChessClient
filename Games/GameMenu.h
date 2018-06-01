#pragma once

#include "../ConsoleWriter.h"
#include "SimpleGame.h"
#include "NetGame.h"

class GameMenu
{
private:
	int _game_option;

public:
	GameMenu();
	IGame* get_option();
};

