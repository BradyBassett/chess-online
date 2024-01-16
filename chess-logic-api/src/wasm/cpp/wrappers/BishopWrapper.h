#ifndef WRAPPERCLASS_H
#define WRAPPERCLASS_H

#include "../models/Bishop.h"

class BishopWrapper {
private:
  Bishop bishop;
  
public:
  BishopWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;
};
#endif
