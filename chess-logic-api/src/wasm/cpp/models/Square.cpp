#include "Square.h"

Square::Square(int rowIndex, int colIndex, std::unique_ptr<Piece> piece)
  : rowIndex(rowIndex), colIndex(colIndex), piece(std::move(piece)) {
}
