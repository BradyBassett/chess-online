#include "KnightWrapper.h"
#include "emscripten/bind.h"

KnightWrapper::KnightWrapper(PieceColor pieceColor, Square* currentSquare) : knight(pieceColor, *currentSquare) {}

bool KnightWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return knight.isValidMove(*board, *targetSquare);
}

EMSCRIPTEN_BINDINGS(KnightWrapperModule) {
  emscripten::class_<KnightWrapper>("KnightWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &KnightWrapper::isValidMove, emscripten::allow_raw_pointers())
    ;
}