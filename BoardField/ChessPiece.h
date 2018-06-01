#pragma once

#include <string>

#include "BoardField.h"

class ChessPiece {
protected:
	const char* _filename = nullptr;
	bool _is_white;
	bool _is_king = false;
	int _piece_type = 0;

	bool check_move(FieldYX next_field, BoardField* current_arrangement[][8], bool& opponent_met, bool pawn = false);

public:

	virtual std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]) = 0;
	bool is_white() const { return _is_white; }
	bool is_king() const { return _is_king; }
	int type() const { return _piece_type; }
	const char* filename() const { return _filename; }

	static const int BISHOP_TYPE = 1;
	static const int KING_TYPE = 2;
	static const int KNIGHT_TYPE = 3;
	static const int PAWN_TYPE = 4;
	static const int QUEEN_TYPE = 5;
	static const int ROOK_TYPE = 6;
};

class Bishop : public ChessPiece {
public:
	Bishop(bool is_w = true) {
		_piece_type = BISHOP_TYPE;
		_is_white = is_w;
		if (_is_white) {
			_filename = "chess_figures/w_bishop.png";
		}
		else {
			_filename = "chess_figures/b_bishop.png";
		}
	};

	std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]);
};

class King : public ChessPiece {
public:
	King(bool is_w = true) {
		_piece_type = KING_TYPE;
		_is_white = is_w;
		_is_king = true;
		if (_is_white) {
			_filename = "chess_figures/w_king.png";
		}
		else {
			_filename = "chess_figures/b_king.png";
		}
	};

	std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]);
};

class Knight : public ChessPiece {
public:
	Knight(bool is_w = true) {
		_piece_type = KNIGHT_TYPE;
		_is_white = is_w;
		if (_is_white) {
			_filename = "chess_figures/w_knight.png";
		}
		else {
			_filename = "chess_figures/b_knight.png";
		}
	};

	std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]);
};

class Pawn : public ChessPiece {
public:
	Pawn(bool is_w = true) {
		_is_white = is_w;
		_piece_type = PAWN_TYPE;
		if (_is_white) {
			_filename = "chess_figures/w_pawn.png";
		}
		else {
			_filename = "chess_figures/b_pawn.png";
		}
	};

	std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]);
};

class Queen : public ChessPiece {
public:
	Queen(bool is_w = true) {
		_piece_type = QUEEN_TYPE;
		_is_white = is_w;
		if (_is_white) {
			_filename = "chess_figures/w_queen.png";
		}
		else {
			_filename = "chess_figures/b_queen.png";
		}
	};

	std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]);
};

class Rook : public ChessPiece {
public:
	Rook(bool is_w = true) {
		_piece_type = ROOK_TYPE;
		_is_white = is_w;
		if (_is_white) {
			_filename = "chess_figures/w_rook.png";
		}
		else {
			_filename = "chess_figures/b_rook.png";
		}
	};

	std::vector<FieldYX> get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8]);
};