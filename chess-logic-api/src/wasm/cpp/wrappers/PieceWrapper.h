#ifndef PIECEWRAPPER_H
#define PIECEWRAPPER_H

#include "../models/Piece.h"
#include <emscripten/bind.h>

class PieceWrapper {
protected:
  Piece piece;

public:
  PieceWrapper(PieceColor pieceColor, Square* currentSquare);

  bool isValidMove(Board* board, Square* targetSquare) const;

  bool getHasMoved() const;

  bool getIsCaptured() const;

	PieceColor getPieceColor() const;

	PieceType getPieceType() const;

	emscripten::val getCurrentSquare() const;

  Piece getPiece() const;
};

#endif
