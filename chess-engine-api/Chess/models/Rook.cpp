#include "Rook.h"

Rook::Rook(Color pieceColor, Position currentPosition, Side side)
		: Piece(pieceColor, currentPosition),
		StraightPiece(pieceColor, currentPosition),
		side(side) {
	pieceType = PieceType::Rook;
}

Side Rook::getSide() const {
	return side;
}