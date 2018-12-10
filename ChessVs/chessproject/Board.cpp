#include "Board.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include <string>
#include <iostream>
#define KING 'k'
#define BISHOP 'b'
#define QUEEN 'q'
#define ROOK 'r'
#define PAWN 'p'
#define KNIGHT 'n'
#define EMPTY '#'
#define OUTSIDE 7


Board::Board(std::string boardStr = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1")
{
	init(boardStr);
}
Board::Board(const Board& b)
{
	_whiteKing = b._whiteKing;
	_blackKing = b._blackKing;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (b._pieces[i][j] != nullptr)
				_pieces[i][j] = b._pieces[i][j]->clone();
			else
				_pieces[i][j] = nullptr;
		}
	}
}
Board::~Board()
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			if (_pieces[row][column] != nullptr)
				delete _pieces[row][column];
		}
	}
}

std::array<std::array<Piece*, SIZE>, SIZE> Board::get_pieces() const
{
	return _pieces;
}
void Board::set_piece(int xPos, int yPos, Piece* p)
{
	_pieces[xPos][yPos] = p;
}
std::array<Piece*, SIZE> Board::operator[](int i) const
{
	if (i > SIZE || i < 0)
		throw std::out_of_range("Index out of range.");
	return _pieces[i];
}

void Board::move_piece(int xSrc, int ySrc, int xDst, int yDst)
{
	_pieces[xSrc][ySrc]->set_x(xDst);
	_pieces[xSrc][ySrc]->set_y(yDst);
	_pieces[xDst][yDst] = _pieces[xSrc][ySrc]->clone();
	delete _pieces[xSrc][ySrc];
	_pieces[xSrc][ySrc] = nullptr;

	_pieces[xDst][yDst]->set_first_turn();

	if (_pieces[xDst][yDst]->to_string() == 'k')
		_blackKing = (King*)_pieces[xDst][yDst];
	else if(_pieces[xDst][yDst]->to_string() == 'K')
		_whiteKing = (King*)_pieces[xDst][yDst];
}
bool Board::is_checkmate(bool whiteChecked) const
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (_pieces[i][j] != nullptr && _pieces[i][j]->get_is_white() == whiteChecked)
			{
				for (int k = 0; k < SIZE; k++)
				{
					for (int l = 0; l < SIZE; l++)
					{
						if (_pieces[i][j]->is_valid_move(k, l, *this))
							return false;
					}
				}
			}
		}
	}
	return true;
}
void Board::init(std::string boardStr)
{
	int column = 0, row = 0;
	bool isWhite = false;
	for (row = 0; row < 8; row++)
	{
		for (column = 0; column < 8; column++)
		{
			int stringIndex = row * SIZE + column;
			isWhite = !islower(boardStr[stringIndex]);	//checking which color is the unit
			boardStr[stringIndex] = tolower(boardStr[stringIndex]);


			switch (boardStr[stringIndex])
			{
			case KING:
				if (isWhite)
					_whiteKing = new King(isWhite, row, column);
				else
					_blackKing = new King(isWhite, row, column);
				_pieces[row][column] = isWhite ? _whiteKing : _blackKing;
				break;
			case QUEEN:
				_pieces[row][column] = new Queen(isWhite, row, column);
				break;
			case ROOK:
				_pieces[row][column] = new Rook(isWhite, row, column);
				break;
			case KNIGHT:
				_pieces[row][column] = new Knight(isWhite, row, column);
				break;
			case BISHOP:
				_pieces[row][column] = new Bishop(isWhite, row, column);
				break;
			case PAWN:
				_pieces[row][column] = new Pawn(isWhite, row, column);
				break;
			case EMPTY:
				_pieces[row][column] = nullptr;
				break;
			default:
				std::cerr << "Invalid character in game string" << std::endl;
				break;
			}

		}
	}
}
int Board::move(int xSrc, int ySrc, int xDst, int yDst, bool turn)
{
	int returnCode = 0;
	if ((xSrc > OUTSIDE || xSrc < 0) ||
		(ySrc > OUTSIDE || ySrc < 0) ||
		(xDst > OUTSIDE || xDst < 0) ||
		(yDst > OUTSIDE || yDst < 0))
	{
		return INVALID_COORDINATE;	//can move a units out of range of the board it will fall of
	}
	if (xSrc == xDst && ySrc == yDst)
		return COORDINATE_EQUALS_CURRENT;
	else
	{
		if (_pieces[xSrc][ySrc] != nullptr)
		{
			if (_pieces[xSrc][ySrc]->get_is_white() != turn)
				return NO_PIECE_SELECTED;
			returnCode = _pieces[xSrc][ySrc]->is_valid_move(xDst, yDst, *this);

			Board toCheck(*this);
			toCheck.move_piece(xSrc, ySrc, xDst, yDst);
			if (turn)
			{
				if (toCheck._whiteKing->is_checked(toCheck._whiteKing->get_x(), toCheck._whiteKing->get_y(), toCheck))
					return MOVEMENT_MAKE_CHECK;
				if (toCheck._blackKing->is_checked(toCheck._blackKing->get_x(), toCheck._blackKing->get_y(), toCheck))
					returnCode = GOOD_MOVE_WITH_CHECK;
			}
			else
			{
				if (toCheck._blackKing->is_checked(_blackKing->get_x(), toCheck._blackKing->get_y(), toCheck))
					return MOVEMENT_MAKE_CHECK;
				if (toCheck._whiteKing->is_checked(_whiteKing->get_x(), toCheck._whiteKing->get_y(), toCheck))
					returnCode = GOOD_MOVE_WITH_CHECK;

			}
			if (returnCode == GOOD_MOVE)
			{
				move_piece(xSrc, ySrc, xDst, yDst);
			}
			else if (returnCode == GOOD_MOVE_WITH_CHECK)
			{
				move_piece(xSrc, ySrc, xDst, yDst);
				if (is_checkmate(!turn))
					return CHECKMATE;
			}
			return returnCode;
		}
		else
			return NO_PIECE_SELECTED;
	}

}
std::string Board::to_string() const
{
	std::string boardStr = "";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (_pieces[i][j] != nullptr)
				boardStr += _pieces[i][j]->to_string();
			else
				boardStr += EMPTY;
		}
	}
	return boardStr;
}
