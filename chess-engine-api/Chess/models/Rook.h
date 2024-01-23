#ifndef ROOK_H
#define ROOK_H

#include "StraightPiece.h"

class Rook : public StraightPiece {
public:
  Rook(PieceColor pieceColor, Square& currentSquare);
};

#endif