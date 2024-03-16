#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : virtual public Piece
{
private:
	const int singleStepDirection = pieceColor == Color::White ? 1 : -1;
	const int doubleStepDirection = pieceColor == Color::White ? 2 : -2;

public:
	Pawn(Color pieceColor, Position currentPosition);

	bool canMoveOneSquare(Position targetPosition) const;

	bool canMoveTwoSquares(Position targetPosition) const;

	bool canPromote(Position targetPosition) const override;

	Bitboard generateAttacks() const;
};

#endif