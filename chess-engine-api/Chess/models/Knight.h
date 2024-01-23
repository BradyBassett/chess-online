#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : virtual public Piece {
  public:
  Knight(PieceColor pieceColor, Square& currentSquare);

  bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif