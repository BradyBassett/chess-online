#include "QueenWrapper.h"
#include "emscripten/bind.h"

QueenWrapper::QueenWrapper(PieceColor pieceColor, Square* currentSquare) : queen(pieceColor, *currentSquare) {}

bool QueenWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return queen.isValidMove(*board, *targetSquare);
}

EMSCRIPTEN_BINDINGS(QueenWrapperModule) {
  emscripten::class_<QueenWrapper>("QueenWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &QueenWrapper::isValidMove)
    ;
}