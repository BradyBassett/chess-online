#include "RookWrapper.h"
#include "emscripten/bind.h"

RookWrapper::RookWrapper(PieceColor pieceColor, Square* currentSquare) : rook(pieceColor, *currentSquare) {}

bool RookWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return rook.isValidMove(*board, *targetSquare);
}

EMSCRIPTEN_BINDINGS(RookWrapperModule) {
  emscripten::class_<RookWrapper>("RookWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &RookWrapper::isValidMove)
    ;
}