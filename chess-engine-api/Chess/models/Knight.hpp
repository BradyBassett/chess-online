#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : virtual public Piece
{
public:
	Knight(Color pieceColor, Position currentPosition);

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif // KNIGHT_HPP