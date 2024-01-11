#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : virtual public Piece {
private:
  bool moveOneSquare(Board& board, Square& targetSquare);

  bool moveTwoSquares(Board& board, Square& targetSquare);

public:
  Pawn(PieceColor pieceColor, Square& currentSquare);

  bool isValidMove(Board& board, Square& targetSquare);
};

#endif