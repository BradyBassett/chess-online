#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "Piece.h"

class OrthagonalPiece : virtual public Piece
{
public:
	using Piece::Piece;

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif
