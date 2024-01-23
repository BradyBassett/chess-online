#include "Rook.h"

Rook::Rook(PieceColor pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare), StraightPiece(pieceColor, currentSquare) {
  pieceType = PieceType::Rook;
}