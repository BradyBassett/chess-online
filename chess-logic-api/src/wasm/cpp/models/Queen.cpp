#include "Queen.h"

Queen::Queen(PieceColor pieceColor, Square& currentSquare) : DiagonalPiece(pieceColor, currentSquare) {
  Piece::pieceType = PieceType::Queen;
}