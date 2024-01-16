#ifndef KINGWRAPPER_H
#define KINGWRAPPER_H

#include "../models/King.h"

class KingWrapper {
private:
  King king;
public:
  KingWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;
};

#endif