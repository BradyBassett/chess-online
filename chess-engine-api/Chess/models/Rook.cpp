#include "Rook.h"

Rook::Rook(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition), StraightPiece(pieceColor, currentPosition) {
	pieceType = PieceType::Rook;
}