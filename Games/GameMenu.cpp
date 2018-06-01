#include "GameMenu.h"

GameMenu::GameMenu()
{
	ConsoleWriter::print_header();
}


IGame* GameMenu::get_option()
{
	int option = ConsoleWriter::get_game_type();
	switch (option)
	{
	case 1:
		return dynamic_cast<IGame*>(new SimpleGame());
		break;
	case 2:
		return dynamic_cast<IGame*>(new NetGame());
		break;
	case 3:
		return nullptr;
    default:
        return nullptr;
	}
}
