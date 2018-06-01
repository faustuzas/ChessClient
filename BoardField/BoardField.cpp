#include "BoardField.h"

BoardField::BoardField() :
	_piece(nullptr)
{

}

bool BoardField::equal_colors(RGBA color1, RGBA color2)
{
	return color1.red == color2.red && color1.green == color2.green && color1.blue == color2.blue && color1.alpha == color2.alpha;
}
