#ifndef DIAGONALPIECE_H
#define DIAGONALPIECE_H

#include "Piece.h"

class DiagonalPiece : virtual public Piece {
private:
  virtual bool isValidDiagonalMove(Board& board, Square& targetSquare) const = 0;

	virtual bool targetSquareIsDiagonal(Square& targetSquare) const = 0;

public:
  using Piece::Piece;

  bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
