#ifndef DIAGONALPIECE_H
#define DIAGONALPIECE_H

#include "Piece.h"

class DiagonalPiece : virtual public Piece {
private:
  virtual bool isValidDiagonalMove(Board& board, Square& targetSquare) const;

	virtual bool targetSquareIsDiagonal(Square& targetSquare) const;

public:
  using Piece::Piece;

  bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
