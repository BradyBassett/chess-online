#ifndef DIAGONALPIECE_H
#define DIAGONALPIECE_H

#include "Piece.h"

class DiagonalPiece : virtual public Piece
{
public:
	using Piece::Piece;

	Bitboard generateAttacks() const;
};

#endif
