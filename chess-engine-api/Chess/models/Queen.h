#ifndef QUEEN_H
#define QUEEN_H

#include "DiagonalPiece.h"
#include "OrthagonalPiece.h"

class Queen : virtual public DiagonalPiece, virtual public OrthagonalPiece
{
public:
	Queen(Color pieceColor, Position currentPosition);

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif
