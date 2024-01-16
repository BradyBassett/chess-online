#ifndef PAWNWRAPPER_H
#define PAWNWRAPPER_H

#include "../models/Pawn.h"

class PawnWrapper {
private:
  Pawn pawn;
public:
  PawnWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;
};

#endif