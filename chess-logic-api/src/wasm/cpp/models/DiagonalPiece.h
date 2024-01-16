#ifndef DIAGONALPIECE_H
#define DIAGONALPIECE_H

#include "Piece.h"

class DiagonalPiece : virtual public Piece {
private:
  bool isValidDiagonalMove(Board& board, Square& targetSquare) const;

	bool targetSquareIsDiagonal(Square& targetSquare) const;

public:
  using Piece::Piece;

  bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
