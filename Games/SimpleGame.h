#pragma once

#include <fstream>
#include "IGame.h"

class SimpleGame : public IGame
{
private:
	const char* FILE_SAVE = "db.txt";

	bool load_from_file();
	void save_to_file();
	bool check_if_save_exists();

public:
	SimpleGame();

	void init();
	void play();
};

