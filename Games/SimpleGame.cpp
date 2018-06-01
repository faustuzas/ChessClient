#include "SimpleGame.h"

#include <iostream>
#include <string>

SimpleGame::SimpleGame() 
{
	_white_turn = true;
}

void SimpleGame::init() 
{
	bool load = false;
	if (check_if_save_exists()) {
		load = ConsoleWriter::ask_to_load_save();
	}

	_window_manager.create_window();

	if (load && load_from_file()) {
		return;
	}

	init_board_fields();
}

void SimpleGame::play()
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
				if (event.button.button == SDL_BUTTON_LEFT) {
					BoardField* field_clicked = find_field(event.button.x, event.button.y);
					if (!on_field_click(field_clicked))
					{
						ConsoleWriter::salute(_white_turn);
						remove(FILE_SAVE);
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

		save_to_file();
	}
}

bool SimpleGame::check_if_save_exists()
{
	std::ifstream f(FILE_SAVE);
	return f.good();
}

bool SimpleGame::load_from_file()
{
	std::fstream file;
	file.open(FILE_SAVE, std::ios::in);

	if (file.is_open()) {

		int field_width = _window_manager.window_width() / 8;
		int field_height = _window_manager.window_height() / 8;

		char turn = file.get();
		_white_turn = turn == '1' ? true : false;

		// remove '\n'
		file.get();

		bool is_white = false;
		int piece_type = 0;

		for (int i = 0; i < 8; i++) {

			int index_for_color = i % 2 == 0;

			for (int j = 0; j < 8; j++) {

				auto* field = new BoardField;
				is_white = false;
				field->coordinates({ i, j });
				piece_type = 0;

				if (file.good()) {
					char tmp = file.get();
					if (tmp != '@') {
						is_white = (bool)(tmp - '0');
						piece_type = (int)file.get() - '0';
					}
					else {
						piece_type = -1;
					}
					// remove '\n'
					file.get();
				}
				else {
					return false;
				}

				// assign color
				if (index_for_color++ % 2 == 0) {
					field->current_color(field->LIGHT_FIELD_COLOR); 
					field->default_color(field->LIGHT_FIELD_COLOR);
				}
				else {
					field->current_color(field->DARK_FIELD_COLOR);
					field->default_color(field->DARK_FIELD_COLOR);
				}

				// assing dimensions
				field->rect({ j * field_width, i * field_height, field_width, field_width });

				// assign piece
				std::shared_ptr<ChessPiece> piece;
				if (piece_type != -1) {
					switch (piece_type) {
					case ChessPiece::BISHOP_TYPE:
						piece = (std::shared_ptr<ChessPiece>) new Bishop(is_white);
						break;
					case ChessPiece::KING_TYPE:
						piece = (std::shared_ptr<ChessPiece>) new King(is_white);
						break;
					case ChessPiece::KNIGHT_TYPE:
						piece = (std::shared_ptr<ChessPiece>) new Knight(is_white);
						break;
					case ChessPiece::PAWN_TYPE:
						piece = (std::shared_ptr<ChessPiece>) new Pawn(is_white);
						break;
					case ChessPiece::QUEEN_TYPE:
						piece = (std::shared_ptr<ChessPiece>) new Queen(is_white);
						break;
					case ChessPiece::ROOK_TYPE:
						piece = (std::shared_ptr<ChessPiece>) new Rook(is_white);
						break;
					default:
						return false;
					}
				}
				
				field->piece(piece);

				// put field into array
				_board_fields[i][j] = field;

				std::string filename = field->piece() != nullptr ? field->piece()->filename() : "null";
			}
		}

		file.close();
		return true;
	}
	else {
		return false;
	}
}

void SimpleGame::save_to_file()
{
	std::fstream file;
	file.open(FILE_SAVE, std::ios::out);

	if (file.is_open()) {
		file << _white_turn << std::endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (_board_fields[i][j]->piece() != nullptr) {
					file << _board_fields[i][j]->piece()->is_white() << _board_fields[i][j]->piece()->type() << std::endl;
				}
				else {
					file << '@' << std::endl;
				}
			}
		}

		file.close();
	}
}