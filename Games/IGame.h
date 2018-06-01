#pragma once

#include "../SDL_Manager.h"
#include "../structs.h"
#include "../ConsoleWriter.h"

#include "../BoardField/ChessPiece.h"

class IGame
{
protected:
	bool _white_turn;
	SDL_Manager _window_manager;
	BoardField* _board_fields[8][8];
	BoardField* _selected_field;

	virtual void init() = 0;
	virtual void play() = 0;
	void clear_board_fields();
	void set_default_colors();
	BoardField* find_field(int y, int x);
	void init_board_fields();
	bool on_field_click(BoardField* field_clicked);
public:
	IGame();
	virtual ~IGame();


	void start_game() { init(); play(); }
	bool white_won() const { return _white_turn; }
};