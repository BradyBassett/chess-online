#ifndef ROOKWRAPPER_H
#define ROOKWRAPPER_H

#include "../models/Rook.h"

class RookWrapper {
private:
  Rook rook;
public:
  RookWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;
};

#endif