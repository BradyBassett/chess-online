#include "Rook.h"

Rook::Rook(Color pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare), StraightPiece(pieceColor, currentSquare) {
	pieceType = PieceType::Rook;
}