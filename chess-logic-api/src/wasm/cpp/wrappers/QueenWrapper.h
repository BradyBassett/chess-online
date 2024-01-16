#ifndef QUEENWRAPPER_H
#define QUEENWRAPPER_H

#include "../models/Queen.h"

class QueenWrapper {
private:
  Queen queen;
public:
  QueenWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;
};

#endif