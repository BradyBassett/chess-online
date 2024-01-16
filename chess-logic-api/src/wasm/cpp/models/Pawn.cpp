#include "Pawn.h"
#include "Square.h"

bool Pawn::moveOneSquare(Board& board, Square& targetSquare) const {
  uint8_t moveDirection = pieceColor == PieceColor::Light ? 1 : -1;

  return targetSquare.getRowIndex() == currentSquare.getRowIndex() + moveDirection;
}

bool Pawn::moveTwoSquares(Board& board, Square& targetSquare) const {
  uint8_t moveDirection = pieceColor == PieceColor::Light ? 2 : -2;

  return targetSquare.getRowIndex() == currentSquare.getRowIndex() + moveDirection;
}

Pawn::Pawn(PieceColor pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare) {
  pieceType = PieceType::Pawn;
}

bool Pawn::isValidMove(Board& board, Square& targetSquare) const {
  if (!Piece::isValidMove(board, targetSquare)) {
    return false;
  }

  if (getHasMoved()) {
    return moveOneSquare(board, targetSquare);
  }
  else {
    return moveOneSquare(board, targetSquare) || moveTwoSquares(board, targetSquare);
  }
}
