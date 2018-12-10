#include "Rook.h"



Rook::Rook(bool isWhite, int xPos, int yPos) : Piece(isWhite, xPos, yPos)
{
}
Rook::Rook(const Rook& r) : Piece(r._isWhite, r._xPos, r._yPos)
{}
Rook::~Rook()
{
}

Rook* Rook::clone() const
{
	return new Rook(*this);
}

int Rook::is_valid_move(int xDst, int yDst, const Board &b) const
{
	if (xDst == _xPos && _yPos == yDst)
		return COORDINATE_EQUALS_CURRENT;
	if (b[xDst][yDst] != nullptr && b[xDst][yDst]->get_is_white() == _isWhite)
		return ALREDY_PIECE_IN_DST;	// if same color
	if (_xPos == xDst && _yPos != yDst)
	{
		for (int i = _yPos < yDst ? _yPos + 1 : _yPos - 1; _yPos < yDst ? i < yDst : i > yDst; _yPos < yDst ? i++ : i--)
			if (b[_xPos][i] != nullptr)
				return INVALID_MOVEMENT;
	}
	else if (_xPos != xDst && _yPos == yDst)
	{
		for (int i = _xPos < xDst ? _xPos + 1 : _xPos - 1; _xPos < xDst ? i < xDst : i > xDst; _xPos < xDst ? i++ : i--)
			if (b[i][_yPos] != nullptr)
				return INVALID_MOVEMENT;
	}
	else
		return INVALID_MOVEMENT;
	return GOOD_MOVE;
}
char Rook::to_string() const
{
	return _isWhite ? 'R' : 'r';
}
