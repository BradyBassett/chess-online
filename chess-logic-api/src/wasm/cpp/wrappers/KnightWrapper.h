#ifndef KNIGHTWRAPPER_H
#define KNIGHTWRAPPER_H

#include "../models/Knight.h"

class KnightWrapper {
private:
  Knight knight;
public:
  KnightWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;
};

#endif