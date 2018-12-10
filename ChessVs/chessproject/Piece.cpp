#include "Piece.h"



Piece::Piece(bool isWhite, unsigned xPos, unsigned yPos)
{
	_isWhite = isWhite;
	_xPos = xPos;
	_yPos = yPos;
}
Piece::~Piece()
{
}

bool Piece::get_is_white() const
{
	return _isWhite;
}
void Piece::set_x(unsigned x)
{
	_xPos = x;
}
int Piece::get_x() const
{
	return _xPos;
}
void Piece::set_y(unsigned y)
{
	_yPos = y;
}
int Piece::get_y() const
{
	return _yPos;
}
void Piece::set_first_turn()
{
}
