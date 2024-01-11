#include "Bishop.h"

Bishop::Bishop(PieceColor pieceColor, Square& square) : DiagonalPiece(pieceColor, currentSquare) {
  pieceType = PieceType::Bishop;
}
