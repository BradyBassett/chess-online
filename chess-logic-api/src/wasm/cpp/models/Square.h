#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include "Piece.h"

class Square {
public:
  int rowIndex;
  int colIndex;
  std::unique_ptr<Piece> piece;

  Square(int rowIndex, int colIndex, std::unique_ptr<Piece> piece = nullptr);
};

#endif
