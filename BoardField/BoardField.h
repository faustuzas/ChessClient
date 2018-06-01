#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#include "../structs.h"

class ChessPiece;

class BoardField
{
private:
	// Members
	std::shared_ptr<ChessPiece> _piece;
	SDL_Rect _rect;
	FieldYX _coordinates;
	RGBA _default_color;
	RGBA _current_color;

public:

	// Constructor
	BoardField();

	// Methods
	void remove_piece() { _piece = nullptr; }
	static bool equal_colors (RGBA color1, RGBA color2);

	// Getters
	std::shared_ptr<ChessPiece>& piece() { return _piece; }
	SDL_Rect& rect() { return _rect; }
	RGBA current_color() const { return _current_color; }
	RGBA default_color() const { return _default_color; }
	FieldYX coordinates() const { return _coordinates; }

	// Setters
	void current_color(RGBA color) { _current_color = color; }
	void default_color(RGBA color) { _default_color = color; }
	void rect(SDL_Rect rect) { _rect = rect; }
	void piece(std::shared_ptr<ChessPiece>& piece) { _piece = piece; }
	void coordinates(FieldYX coordinates) { _coordinates = coordinates; }

	// Constants
	RGBA ACTIVE_COLOR		 = { 178,  47, 24, 255 };
	RGBA POSSIBLE_MOVE_COLOR = { 173,  87, 72, 255 };
	RGBA LIGHT_FIELD_COLOR   = { 196, 127, 43, 255 };
	RGBA DARK_FIELD_COLOR	 = {  56,  34,  7, 255 };
};
