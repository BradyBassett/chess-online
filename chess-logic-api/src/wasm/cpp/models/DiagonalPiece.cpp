#include "DiagonalPiece.h"
#include "Square.h"
#include "Board.h"

bool DiagonalPiece::isValidDiagonalMove(Board& board, Square& targetSquare) const {
  uint8_t rowStep = (targetSquare.getRowIndex() - currentSquare.getRowIndex()) > 0 ? 1 : -1;
  uint8_t colStep = (targetSquare.getColIndex() - currentSquare.getColIndex()) > 0 ? 1 : -1;

  uint8_t i = currentSquare.getRowIndex() + rowStep;
  uint8_t j = currentSquare.getColIndex() + colStep;

  while ((rowStep > 0 ? i <targetSquare.getRowIndex() : i > targetSquare.getRowIndex()) &&
         (colStep > 0 ? j < targetSquare.getColIndex() : j > targetSquare.getColIndex())) {
    if (board.getSquare(i, j).getPiece() != nullptr) {
      return false;
    }

    i += rowStep;
    j += colStep;
  }

  return true;
}

bool DiagonalPiece::targetSquareIsDiagonal(Square& targetSquare) const {
  return abs(targetSquare.getRowIndex() - currentSquare.getRowIndex()) !=
         abs(targetSquare.getColIndex() - currentSquare.getColIndex());
}

bool DiagonalPiece::isValidMove(Board& board, Square& targetSquare) const {
  if (!Piece::isValidMove(board, targetSquare)) {
    return false;
  }

  if (!targetSquareIsDiagonal(targetSquare)) {
    return false;
  }

  return isValidDiagonalMove(board, targetSquare);
}
