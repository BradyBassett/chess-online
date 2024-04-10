#ifndef DIAGONALPIECE_HPP
#define DIAGONALPIECE_HPP

#include "Piece.hpp"

class DiagonalPiece : virtual public Piece
{
public:
	using Piece::Piece;

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif // DIAGONALPIECE_HPP
