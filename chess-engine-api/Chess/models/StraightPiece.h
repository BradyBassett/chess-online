#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "Piece.h"
#include "Board.h"

class StraightPiece : virtual public Piece
{
private:
	bool isValidStraightMove(Board &board, Position targetPosition) const;

	bool targetSquareIsStraight(Position targetPosition) const;

public:
	using Piece::Piece;

	bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Board &board) const;
};

#endif
