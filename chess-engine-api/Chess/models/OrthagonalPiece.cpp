#include "OrthagonalPiece.hpp"

Bitboard OrthagonalPiece::generateAttacks() const
{
	Position directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	return Piece::generateAttacks(directions);
}

Bitboard OrthagonalPiece::getPotentialMoves() const
{
	return generateAttacks();
}