#include "Knight.h"



Knight::Knight(bool isWhite, int xPos, int yPos) : Piece(isWhite, xPos, yPos)
{
}
Knight::~Knight()
{
}
Piece* Knight::clone() const
{
	return new Knight(*this);
}

int Knight::is_valid_move(int xDst, int yDst, const Board &b) const
{
	if ((abs(_xPos - xDst) == 2 && abs(_yPos - yDst) == 1) || (abs(_xPos - xDst) == 1 && abs(_yPos - yDst) == 2))
	{
		if (b[xDst][yDst] != nullptr)
		{
			if (b[xDst][yDst]->get_is_white() == _isWhite)
				return 3;
		}
		return 0;
	}
	else
		return 6;
}
char Knight::to_string() const
{
	return _isWhite ? 'N' : 'n';
}
