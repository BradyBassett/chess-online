#include "PieceWrapper.h"
#include "../models/Square.h"

PieceWrapper::PieceWrapper(PieceColor pieceColor, Square* currentSquare) : piece(pieceColor, *currentSquare) {}

bool PieceWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return piece.isValidMove(*board, *targetSquare);
}

bool PieceWrapper::getHasMoved() const {
  return piece.getHasMoved();
}

bool PieceWrapper::getIsCaptured() const {
  return piece.getIsCaptured();
}

PieceColor PieceWrapper::getPieceColor() const {
  return piece.getPieceColor();
}

PieceType PieceWrapper::getPieceType() const {
  return piece.getPieceType();
}

emscripten::val PieceWrapper::getCurrentSquare() const {
  Square square = piece.getCurrentSquare();

  emscripten::val result = emscripten::val::object();

  result.set("rowIndex", square.getRowIndex());
  result.set("colIndex", square.getColIndex());

  return result;
}

Piece PieceWrapper::getPiece() const {
  return piece;
}

EMSCRIPTEN_BINDINGS(PieceWrapperModule) {
  emscripten::class_<PieceWrapper>("PieceWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &PieceWrapper::isValidMove, emscripten::allow_raw_pointers())
    .function("getHasMoved", &PieceWrapper::getHasMoved)
    .function("getIsCaptured", &PieceWrapper::getIsCaptured)
    .function("getPieceColor", &PieceWrapper::getPieceColor)
    .function("getPieceType", &PieceWrapper::getPieceType)
    .function("getCurrentSquare", &PieceWrapper::getCurrentSquare)
    ;
}
