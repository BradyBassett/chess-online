#include <algorithm>
#include "Piece.h"

Piece::Piece(PieceColor pieceColor, Square& currentSquare)
  : pieceColor(pieceColor),
    currentSquare(currentSquare) {
}

bool Piece::isValidDiagonalMove(Board& board, Square& targetSquare) const {
  u_int8_t rowStep = (targetSquare.getRowIndex() - currentSquare.getRowIndex()) > 0 ? 1 : -1;
  u_int8_t colStep = (targetSquare.getColIndex() - currentSquare.getColIndex()) > 0 ? 1 : -1;

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

bool Piece::targetSquareIsDiagonal(Square& targetSquare) const {
  return abs(targetSquare.getRowIndex() - currentSquare.getRowIndex()) !=
         abs(targetSquare.getColIndex() - currentSquare.getColIndex());
}

bool Piece::isValidStraightMove(Board& board, Square& targetSquare) const {
  if (targetSquare.getRowIndex() == currentSquare.getRowIndex()) {
    u_int8_t rowStart = std::min(targetSquare.getColIndex(), currentSquare.getColIndex());
    u_int8_t rowEnd = std::max(targetSquare.getColIndex(), currentSquare.getColIndex());

    for (u_int8_t i = rowStart + 1; i < rowEnd - 1; i++) {
      if (board.getSquare(currentSquare.getRowIndex(), i).getPiece()) {
        return false;
      }
    }
  }
  else if (targetSquare.getColIndex() == currentSquare.getColIndex()) {
    u_int8_t colStart = std::min(targetSquare.getRowIndex(), currentSquare.getRowIndex());
    u_int8_t colEnd = std::max(targetSquare.getRowIndex(), currentSquare.getRowIndex());

    for (u_int8_t i = colStart + 1; i < colEnd - 1; i++) {
      if (board.getSquare(i, currentSquare.getColIndex()).getPiece()) {
        return false;
      }
    }
  }
  
  return true;
}

bool Piece::targetSquareIsStraight(Square& targetSquare) const {
  return targetSquare.getRowIndex() == currentSquare.getRowIndex() || targetSquare.getColIndex() == currentSquare.getColIndex();
}

bool Piece::isValidMove(Board& board, Square& targetSquare) const {
  if (&targetSquare == &currentSquare) {
    return false;
  }

  if (targetSquare.getPiece() && targetSquare.getPiece()->getPieceColor() == pieceColor) {
    return false;
  }

  return true;
}

bool Piece::getHasMoved() const {
  return hasMoved;
}

bool Piece::getIsCaptured() const {
  return isCaptured;
}

PieceColor Piece::getPieceColor() const {
  return pieceColor;
}

PieceType Piece::getPieceType() const {
  return pieceType;
}