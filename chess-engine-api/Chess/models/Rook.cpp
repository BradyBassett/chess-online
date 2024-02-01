#include "Rook.h"

Rook::Rook(Color pieceColor, std::shared_ptr<Square> currentSquare) : Piece(pieceColor, currentSquare), StraightPiece(pieceColor, currentSquare) {
	pieceType = PieceType::Rook;
}