#include "Square.h"

Square::Square(int rowIndex, int colIndex, std::shared_ptr<Piece> piece)
  : rowIndex(rowIndex), colIndex(colIndex), piece(std::move(piece)) {
}

Square::Square(const Square& square)
  : rowIndex(square.rowIndex), colIndex(square.colIndex), piece(std::move(square.piece)) {
}

u_int8_t Square::getRowIndex() const {
  return rowIndex;
}

u_int8_t Square::getColIndex() const {
  return colIndex;
}

std::shared_ptr<Piece> Square::getPiece() const {
  return piece;
}