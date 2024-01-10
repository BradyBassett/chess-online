#include "Square.h"

Square::Square(int rowIndex, int colIndex, std::shared_ptr<Piece> piece)
  : rowIndex(rowIndex), colIndex(colIndex), piece(std::move(piece)) {
}

Square::Square(const Square& square)
  : rowIndex(square.rowIndex), colIndex(square.colIndex), piece(std::move(square.piece)) {
}
