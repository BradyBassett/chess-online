#include "King.h"
#include "../utils/structs/Move.h"

King::King(PieceColor pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare) {
  pieceType = PieceType::King;
}

bool King::isValidMove(Board& board, Square& targetSquare) {
  if (!Piece::isValidMove(board, targetSquare)) {
    return false;
  }

  Move moves[] = {
    {1, 0},    // Up
    {1, 1},    // Up-Right
    {0, 1},    // Right
    {-1, 1},   // Down-Right
    {-1, 0},   // Down
    {-1, -1},  // Down-Left
    {0, -1},   // Left
    {1, -1}    // Up-Left
  };

  for (const auto& move : moves) {
    if (targetSquare.getRowIndex() == currentSquare.getRowIndex() + move.row &&
        targetSquare.getColIndex() == currentSquare.getColIndex() + move.col) {
      return true;
    }
  }

  return false;
}
