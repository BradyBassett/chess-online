#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "Piece.h"

class StraightPiece : virtual public Piece {
private:
	bool isValidStraightMove(Board& board, Square& targetSquare) const;

	bool targetSquareIsStraight(Square& targetSquare) const;
	
public:
	using Piece::Piece;

	bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
