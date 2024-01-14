#include "Queen.h"

Queen::Queen(PieceColor pieceColor, Square& currentSquare) 
    : Piece(pieceColor, currentSquare), DiagonalPiece(pieceColor, currentSquare), StraightPiece(pieceColor, currentSquare) {
  pieceType = PieceType::Queen;
}
