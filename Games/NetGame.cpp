#include "NetGame.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>  

NetGame::NetGame()
{
	_white_turn = true;
}

NetGame::~NetGame()
{
	_connection.close_connection();
}

void NetGame::init()
{
	_connection.init(ConsoleWriter::get_ip());

	_player_is_white = determine_player_color();

	_window_manager.create_window();

	init_board_fields();
}

bool NetGame::determine_player_color()
{
	std::cout << "Conecting..." << std::endl;
	srand((unsigned int)time(NULL));

	while (true) {
		std::string my_identifier = std::to_string(rand() % 100);
		std::string enemy_identifier;

		while (true) {
			_connection.send(my_identifier.c_str());
			const char* data_got = _connection.check_for_data();
			if (data_got != nullptr) {
				enemy_identifier = data_got;
				break;
			}
		}

		int result = my_identifier.compare(enemy_identifier);

		if (result == 0) continue;

		return result == 1;
	}
}

void NetGame::play()
{
	SDL_Event event;

	while (true)
	{
		_window_manager.render_board(_board_fields);

		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			return;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && _player_is_white == _white_turn) {
				BoardField* field_clicked = find_field(event.button.x, event.button.y);
				if (on_field_click(field_clicked))
				{
					std::string data = std::to_string(field_clicked->coordinates().y) + std::to_string(field_clicked->coordinates().x);
					_connection.send(data.c_str());
				}
				else {
					// send notification that you won
					const char* won = "XX";
					_connection.send(won);
					ConsoleWriter::you_won();
					return;
				}

				if (_selected_field == nullptr) {
					set_default_colors();
				}

				break;
			}
		default:
			break;
		}

		if (_player_is_white != _white_turn) {
			const char* data_got = _connection.check_for_data();
			if (data_got != nullptr) {

				if (strcmp(data_got, "XX") == 0) {
					ConsoleWriter::you_lost();
					return;
				}

				int y = data_got[0] - '0';
				int x = data_got[1] - '0';

				on_field_click(_board_fields[y][x]);

				if (_selected_field == nullptr) {
					set_default_colors();
				}
			}
		}
	}
}