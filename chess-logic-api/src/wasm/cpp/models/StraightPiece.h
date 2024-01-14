#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "Piece.h"

class StraightPiece : virtual public Piece {
private:
  virtual bool isValidStraightMove(Board& board, Square& targetSquare) const;

	virtual bool targetSquareIsStraight(Square& targetSquare) const;
  
public:
  using Piece::Piece;

  bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
