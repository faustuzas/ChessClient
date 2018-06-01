#include "ChessPiece.h"

bool ChessPiece::check_move(FieldYX next_field, BoardField* current_arrangement[][8], bool& opponent_met, bool pawn)
{
	// if field falls in board range 
	bool condition_board_dimensions = next_field.x <= 7 && next_field.y <= 7 && next_field.x >= 0 && next_field.y >= 0;
	if (condition_board_dimensions) {

		// if field is occupied
		bool condition_piece_met = current_arrangement[next_field.y][next_field.x]->piece() != nullptr;
		if (condition_piece_met) {
			bool condition_friendly_piece = current_arrangement[next_field.y][next_field.x]->piece()->is_white() == is_white();

			//if field is occupied by friend
			if (condition_friendly_piece) {
				return false;
			}
			else {
				// if field is occupied by opponent, if the piece is pawn return false
				opponent_met = true;
				return !pawn;
			}
			return false;

		}
		else {
			//if field is empty
			return true;
		}

	}
	else {
		return false;
	}
}

// Bishop
std::vector<FieldYX> Bishop::get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8])
{
	std::vector <FieldYX> possible_moves;
	FieldYX next_move;
	bool opponent_met;

	// NE
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y - 1, next_move.x + 1 }, current_arrangement, opponent_met)) {
		next_move.x++;
		next_move.y--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// NW
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y - 1, next_move.x - 1 }, current_arrangement, opponent_met)) {
		next_move.x--;
		next_move.y--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// SE
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y + 1, next_move.x + 1 }, current_arrangement, opponent_met)) {
		next_move.x++;
		next_move.y++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// SW
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y + 1, next_move.x - 1 }, current_arrangement, opponent_met)) {
		next_move.x--;
		next_move.y++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	return possible_moves;
}

// King
std::vector<FieldYX> King::get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8])
{
	std::vector <FieldYX> possible_moves;
	bool opponent_met;

	// N
	opponent_met = false;
	if (check_move({ current_spot.y - 1, current_spot.x }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 1, current_spot.x });
	}

	// E
	opponent_met = false;
	if (check_move({ current_spot.y, current_spot.x + 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y, current_spot.x + 1 });
	}

	// S
	opponent_met = false;
	if (check_move({ current_spot.y + 1, current_spot.x }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 1, current_spot.x });
	}

	// W
	opponent_met = false;
	if (check_move({ current_spot.y, current_spot.x - 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y, current_spot.x - 1 });
	}

	// NE
	opponent_met = false;
	if (check_move({ current_spot.y - 1, current_spot.x + 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 1, current_spot.x + 1 });
	}

	// NW
	opponent_met = false;
	if (check_move({ current_spot.y - 1, current_spot.x - 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 1, current_spot.x - 1 });
	}

	// SE
	opponent_met = false;
	if (check_move({ current_spot.y + 1, current_spot.x + 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 1, current_spot.x + 1 });
	}

	// SW
	opponent_met = false;
	if (check_move({ current_spot.y + 1, current_spot.x - 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 1, current_spot.x - 1 });
	}

	return possible_moves;
}

// Knight
std::vector<FieldYX> Knight::get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8])
{
	std::vector <FieldYX> possible_moves;
	bool opponent_met;

	// NNE
	opponent_met = false;
	if (check_move({ current_spot.y - 2, current_spot.x + 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 2, current_spot.x + 1 });
	}

	// NNW
	opponent_met = false;
	if (check_move({ current_spot.y - 2, current_spot.x - 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 2, current_spot.x - 1 });
	}

	// EEN
	opponent_met = false;
	if (check_move({ current_spot.y - 1, current_spot.x + 2 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 1, current_spot.x + 2 });
	}

	// EES
	opponent_met = false;
	if (check_move({ current_spot.y + 1, current_spot.x + 2 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 1, current_spot.x + 2 });
	}

	// SSE
	opponent_met = false;
	if (check_move({ current_spot.y + 2, current_spot.x + 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 2, current_spot.x + 1 });
	}

	// SSW
	opponent_met = false;
	if (check_move({ current_spot.y + 2, current_spot.x - 1 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 2, current_spot.x - 1 });
	}

	// WWN
	opponent_met = false;
	if (check_move({ current_spot.y - 1, current_spot.x - 2 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y - 1, current_spot.x - 2 });
	}

	// WWS
	opponent_met = false;
	if (check_move({ current_spot.y + 1, current_spot.x - 2 }, current_arrangement, opponent_met)) {
		possible_moves.push_back({ current_spot.y + 1, current_spot.x - 2 });
	}

	return possible_moves;
}

// Pawn
std::vector<FieldYX> Pawn::get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8])
{
	std::vector<FieldYX> possible_moves;
	bool opponent_met = false;

	// moving
	if (_is_white) {
		if (check_move({ current_spot.y + 1, current_spot.x }, current_arrangement, opponent_met, true)) {
			possible_moves.push_back({ current_spot.y + 1, current_spot.x });
		}
		if (!opponent_met && current_spot.y == 1) {
			if (check_move({ current_spot.y + 2, current_spot.x }, current_arrangement, opponent_met, true)) {
				possible_moves.push_back({ current_spot.y + 2, current_spot.x });
			}
		}

	}

	if (!_is_white) {
		if (check_move({ current_spot.y - 1, current_spot.x }, current_arrangement, opponent_met, true)) {
			possible_moves.push_back({ current_spot.y - 1, current_spot.x });
		}
		if (!opponent_met && current_spot.y == 6) {
			if (check_move({ current_spot.y - 2, current_spot.x }, current_arrangement, opponent_met, true)) {
				possible_moves.push_back({ current_spot.y - 2, current_spot.x });
			}
		}
	}

	// replacing
	if (_is_white) {
		opponent_met = false;
		if (check_move({ current_spot.y + 1, current_spot.x + 1 }, current_arrangement, opponent_met)) {
			if (opponent_met) {
				possible_moves.push_back({ current_spot.y + 1, current_spot.x + 1 });
			}
		}
		opponent_met = false;
		if (check_move({ current_spot.y + 1, current_spot.x - 1 }, current_arrangement, opponent_met)) {
			if (opponent_met) {
				possible_moves.push_back({ current_spot.y + 1, current_spot.x - 1 });
			}
		}
	}

	if (!_is_white) {
		opponent_met = false;
		if (check_move({ current_spot.y - 1, current_spot.x - 1 }, current_arrangement, opponent_met)) {
			if (opponent_met) {
				possible_moves.push_back({ current_spot.y - 1, current_spot.x - 1 });
			}
		}
		opponent_met = false;
		if (check_move({ current_spot.y - 1, current_spot.x + 1 }, current_arrangement, opponent_met)) {
			if (opponent_met) {
				possible_moves.push_back({ current_spot.y - 1, current_spot.x + 1 });
			}
		}
	}

	return possible_moves;
}

// Rook
std::vector<FieldYX> Rook::get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8])
{
	std::vector<FieldYX> possible_moves;
	FieldYX next_move;
	bool opponent_met;

	// N
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y - 1, next_move.x }, current_arrangement, opponent_met)) {
		next_move.y--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// W
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y, next_move.x - 1 }, current_arrangement, opponent_met)) {
		next_move.x--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// S
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y + 1, next_move.x }, current_arrangement, opponent_met)) {
		next_move.y++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// E
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y, next_move.x + 1 }, current_arrangement, opponent_met)) {
		next_move.x++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	return possible_moves;
}

// Queen
std::vector<FieldYX> Queen::get_possible_moves(FieldYX current_spot, BoardField* current_arrangement[][8])
{
	std::vector<FieldYX> possible_moves;
	FieldYX next_move;
	bool opponent_met;

	// N
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y - 1, next_move.x }, current_arrangement, opponent_met)) {
		next_move.y--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// W
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y, next_move.x - 1 }, current_arrangement, opponent_met)) {
		next_move.x--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// S
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y + 1, next_move.x }, current_arrangement, opponent_met)) {
		next_move.y++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// E
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y, next_move.x + 1 }, current_arrangement, opponent_met)) {
		next_move.x++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// NE
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y - 1, next_move.x + 1 }, current_arrangement, opponent_met)) {
		next_move.x++;
		next_move.y--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// NW
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y - 1, next_move.x - 1 }, current_arrangement, opponent_met)) {
		next_move.x--;
		next_move.y--;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// SE
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y + 1, next_move.x + 1 }, current_arrangement, opponent_met)) {
		next_move.x++;
		next_move.y++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	// SW
	next_move = current_spot;
	opponent_met = false;
	while (check_move({ next_move.y + 1, next_move.x - 1 }, current_arrangement, opponent_met)) {
		next_move.x--;
		next_move.y++;
		possible_moves.push_back(next_move);
		if (opponent_met) {
			break;
		}
	}

	return possible_moves;
}