#include "IGame.h"

IGame::IGame() : 
	_selected_field(nullptr),
	_window_manager({ 100, 100, 500, 500 })
{

}

IGame::~IGame()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			delete _board_fields[i][j];
	}
}

void IGame::clear_board_fields()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete _board_fields[i][j];
		}
	}
}

void IGame::set_default_colors()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_board_fields[i][j]->current_color(_board_fields[i][j]->default_color());
		}
	}
}

BoardField* IGame::find_field(int x, int y)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int lower_limit_x = _board_fields[i][j]->rect().x;
			int higher_limit_x = _board_fields[i][j]->rect().x + _board_fields[i][j]->rect().w;

			int lower_limit_y = _board_fields[i][j]->rect().y;
			int higher_limit_y = _board_fields[i][j]->rect().y + _board_fields[i][j]->rect().h;

			bool in_field_area = x >= lower_limit_x && x <= higher_limit_x && y >= lower_limit_y && y <= higher_limit_y;

			if (in_field_area) {
				return _board_fields[i][j];
			}
		}
	}

	return nullptr;
}

void IGame::init_board_fields()
{
	int field_width = _window_manager.window_width() / 8;
	int field_height = _window_manager.window_height() / 8;

	for (int i = 0; i < 8; i++) {

		int index_for_color = i % 2 == 0;

		for (int j = 0; j < 8; j++) {

			auto* field = new BoardField;

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
			field->coordinates({i, j});

			// assign piece
			std::shared_ptr<ChessPiece> piece;
			switch (i) {
			case 0:
				switch (j) {
				case 0:
				case 7:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Rook>());
					break;
				case 1:
				case 6:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Knight>());
					break;
				case 2:
				case 5:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Bishop>());
					break;
				case 3:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<King>());
					break;
				case 4:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Queen>());
					break;
				default:
					break;
				}
				break;
			case 1: // if there is no break in case 0, this case is executed with 0 also
				piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Pawn>());
				break;
			case 6:
				piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Pawn>(false));
				break;
			case 7:
				switch (j) {
				case 0:
				case 7:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Rook>(false));
					break;
				case 1:
				case 6:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Knight>(false));
					break;
				case 2:
				case 5:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Bishop>(false));
					break;
				case 3:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<King>(false));
					break;
				case 4:
					piece = std::dynamic_pointer_cast<ChessPiece>(std::make_shared<Queen>(false));
					break;
				default:
					break;
				}
			default:
				break;
			}

			field->piece(piece);

			// put field into array
			_board_fields[i][j] = field;
		}
	}
}

bool IGame::on_field_click(BoardField* field_clicked)
{
	// if clicked field is neutral
	if (BoardField::equal_colors(field_clicked->current_color(), field_clicked->default_color())) {
		// if there is a piece on the field
		if (field_clicked->piece() != nullptr && field_clicked->piece()->is_white() == _white_turn) {
			// if no field was active before, set this field to active
			if (_selected_field == nullptr) {
				field_clicked->current_color(field_clicked->ACTIVE_COLOR);
				_selected_field = field_clicked;

				// get all possible moves by piece 
				std::vector<FieldYX> possible_moves = field_clicked->piece()->get_possible_moves(field_clicked->coordinates(), _board_fields);

				// color all fields where could piece go
				for (FieldYX field : possible_moves) {
					_board_fields[field.y][field.x]->current_color(field_clicked->POSSIBLE_MOVE_COLOR);
				}
			}
			else {
				// if player changed his mind, reset active field
				_selected_field = nullptr;
			}
		}
		else {
			// if there is no piece on field, reset everything
			_selected_field = nullptr;
		}
	}
	else if (BoardField::equal_colors(field_clicked->current_color(), field_clicked->ACTIVE_COLOR)) {
		// if player clicked on active field, reset it 
		field_clicked->current_color(field_clicked->default_color());
		_selected_field = nullptr;
	}
	else { // if player clicked on possible move field
		
		// if the field clicked had King - stop the game
		if (field_clicked->piece() != nullptr && field_clicked->piece()->is_king()) {
			return false;
		}
		
		// set new piece for the field
		field_clicked->piece(_selected_field->piece());
		_selected_field->remove_piece();

		// change active player
		_white_turn = !_white_turn;

		// reset active field
		_selected_field = nullptr;
	}
	
	// continue game
	return true;
}