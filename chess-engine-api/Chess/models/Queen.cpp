#include "Queen.hpp"

Queen::Queen(Color pieceColor, Position currentPosition)
	: Piece(pieceColor, currentPosition), DiagonalPiece(pieceColor, currentPosition), OrthagonalPiece(pieceColor, currentPosition)
{
	pieceType = PieceType::Queen;
}

Bitboard Queen::generateAttacks() const
{
	Bitboard attacks = 0x0;

	// get attacks for diagonal and orthagonal moves
	attacks |= DiagonalPiece::generateAttacks();
	attacks |= OrthagonalPiece::generateAttacks();

	return attacks;
}

Bitboard Queen::getPotentialMoves() const
{
	return generateAttacks();
}