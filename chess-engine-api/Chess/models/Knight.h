#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Board.h"

class Knight : virtual public Piece
{
private:
	static const Position moves[8];

public:
	Knight(Color pieceColor, Position currentPosition);

	bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Board &board) const;
};

#endif