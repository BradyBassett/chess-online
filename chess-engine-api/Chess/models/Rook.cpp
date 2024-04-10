#include "Rook.hpp"

Rook::Rook(Color pieceColor, Position currentPosition, Side side)
	: Piece(pieceColor, currentPosition),
	  OrthagonalPiece(pieceColor, currentPosition),
	  side(side)
{
	pieceType = PieceType::Rook;
}

Side Rook::getSide() const
{
	return side;
}