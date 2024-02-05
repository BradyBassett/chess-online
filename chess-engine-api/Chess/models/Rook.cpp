#include "Rook.h"

Rook::Rook(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition), StraightPiece(pieceColor, currentPosition) {
	pieceType = PieceType::Rook;

	if (currentPosition.col == 0) {
		side = Side::QueenSide;
	} else {
		side = Side::KingSide;
	}
}

Side Rook::getSide() const {
	return side;
}