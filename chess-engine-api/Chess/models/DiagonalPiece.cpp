#include "DiagonalPiece.hpp"

Bitboard DiagonalPiece::generateAttacks() const
{
	Position directions[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	return Piece::generateAttacks(directions);
}

Bitboard DiagonalPiece::getPotentialMoves() const
{
	return generateAttacks();
}