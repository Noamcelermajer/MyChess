#pragma once
#include "Board.h"
#include "code.h"
#include <string>


class Board;
class Piece
{
protected:
	bool _isWhite;
	int _xPos;
	int _yPos;

public:
	Piece(bool isWhite, unsigned xPos, unsigned yPos);
	virtual ~Piece();

	virtual Piece* clone() const = 0;

	virtual bool get_is_white() const;
	virtual void set_x(unsigned x);
	virtual int get_x() const;
	virtual void set_y(unsigned y);
	virtual int get_y() const;
	virtual void set_first_turn();

	virtual int is_valid_move(int xDst, int yDst, const Board &b) const = 0;
	virtual char to_string() const = 0;
};
