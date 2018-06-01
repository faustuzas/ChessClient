#include "Games/GameMenu.h"

int main(int argc, char* args[])
{
	GameMenu gm;

	while (true) {
		IGame* game = gm.get_option();

		if (game == nullptr) 
			break;

		game->start_game();
		delete game;
	}

	ConsoleWriter::print_goodbye();
	return 0;
}