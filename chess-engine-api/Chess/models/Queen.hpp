#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "DiagonalPiece.hpp"
#include "OrthagonalPiece.hpp"

class Queen : virtual public DiagonalPiece, virtual public OrthagonalPiece
{
public:
	Queen(Color pieceColor, Position currentPosition);

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif // QUEEN_HPP
