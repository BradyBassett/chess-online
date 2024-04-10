#ifndef ORTHAGONALPIECE_HPP
#define ORTHAGONALPIECE_HPP

#include "Piece.hpp"

class OrthagonalPiece : virtual public Piece
{
public:
	using Piece::Piece;

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif // ORTHAGONALPIECE_HPP
