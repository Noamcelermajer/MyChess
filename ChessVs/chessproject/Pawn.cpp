#include "Pawn.h"



Pawn::Pawn(bool isWhite, int xPos, int yPos) : Piece(isWhite, xPos, yPos)
{
	_firstTurn = true;
}
Pawn::~Pawn()
{
}
Pawn::Pawn(const Pawn& r) : Piece(r._isWhite, r._xPos, r._yPos)
{
	_firstTurn = r._firstTurn;
}
Pawn* Pawn::clone() const
{
	return new Pawn(*this);
}

int Pawn::is_valid_move(int xDst, int yDst, const Board &b) const
{
	if (abs(xDst - _xPos) == 1 && abs(yDst - _yPos) == 0)
	{
		if (_isWhite ? (xDst > _xPos) : (xDst < _xPos))
			return INVALID_MOVEMENT;
		else
			if (b[xDst][yDst] == nullptr)
				return GOOD_MOVE;
	}
	else if (abs(xDst - _xPos) == 2 && abs(yDst - _yPos) == 0)
	{
		if (!_firstTurn)
			return INVALID_MOVEMENT;
		if (_isWhite ? (xDst > _xPos) : (xDst < _xPos))
			return INVALID_MOVEMENT;
		else
			if (b[_isWhite ? (_xPos - 1) : (_xPos + 1)][yDst] == nullptr && b[xDst][yDst] == nullptr)
				return GOOD_MOVE;
	}
	else if (abs(xDst - _xPos) == 1 && abs(yDst - _yPos) == 1)
	{
		if (_isWhite ? (xDst > _xPos) : (xDst < _xPos))
			return INVALID_MOVEMENT;
		else
			if (b[xDst][yDst] == nullptr)
				return INVALID_MOVEMENT;
			else if (b[xDst][yDst]->get_is_white() == _isWhite)
				return ALREDY_PIECE_IN_DST;
			else
				return GOOD_MOVE;
	}
	return INVALID_MOVEMENT;
}
void Pawn::set_first_turn()
{
	_firstTurn = false;
}
char Pawn::to_string() const
{
	return _isWhite ? 'P' : 'p';
}
