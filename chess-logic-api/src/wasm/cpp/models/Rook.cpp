#include "Rook.h"

Rook::Rook(PieceColor pieceColor, Square& currentSquare) : StraightPiece(pieceColor, currentSquare) {
  pieceType = PieceType::Rook;
}