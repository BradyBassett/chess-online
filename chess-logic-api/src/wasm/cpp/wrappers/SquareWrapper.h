#ifndef SQUAREWRAPPER_H
#define SQUAREWRAPPER_H

#include "../models/Square.h"
#include "PieceWrapper.h"

class SquareWrapper {
private:
  Square square;
public:
  SquareWrapper(int rowIndex, int colIndex, PieceWrapper* pieceWrapper);

  uint8_t getRowIndex() const;

  uint8_t getColIndex() const;

  PieceWrapper* getPiece() const;

  void setPiece(PieceWrapper* pieceWrapper);
};

#endif