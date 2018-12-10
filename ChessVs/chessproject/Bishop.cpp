#include "Bishop.h"
#include <iostream>
#include <cmath>
#define  ABS 1
Bishop::Bishop(bool isWhite, int xPos, int yPos) : Piece(isWhite, xPos, yPos)
{
}
Bishop::~Bishop()
{
	_isWhite = false;
	_xPos = 0;
	_yPos = 0;
}

Bishop* Bishop::clone() const
{
	return new Bishop(*this);
}

int Bishop::is_valid_move(int xDst, int yDst, const Board &b) const
{
	int x = 0, y = 0, xdir = 0, ydir = 0;
	if (_xPos == xDst && _yPos == yDst)
		return COORDINATE_EQUALS_CURRENT;
	if (b[_xPos][_yPos] == nullptr)
		return NO_PIECE_SELECTED;
	if (b[xDst][yDst] != nullptr && b[xDst][yDst]->get_is_white() == _isWhite)
		return ALREDY_PIECE_IN_DST;
	
	x = xDst - _xPos;
	y = yDst - _yPos;

	xdir = x < 0 ? -ABS : ABS;
	ydir = y < 0 ? -ABS : ABS;

	x *= xdir;
	y *= ydir;
	
	if (x != y)
	{
		return INVALID_MOVEMENT;
	}
	for (int i = _xPos + xdir, j = _yPos + ydir; i != xDst; i += xdir, j += ydir)
	{
		if (b[i][j] != NULL)
		{
			return INVALID_MOVEMENT;
		}
	}
	return GOOD_MOVE;
}
char Bishop::to_string() const
{
	return _isWhite ? 'B' : 'b';
}
