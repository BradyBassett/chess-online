#include "KingWrapper.h"
#include "emscripten/bind.h"

KingWrapper::KingWrapper(PieceColor pieceColor, Square* currentSquare) : king(pieceColor, *currentSquare) {}

bool KingWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return king.isValidMove(*board, *targetSquare);
}

EMSCRIPTEN_BINDINGS(KingWrapperModule) {
  emscripten::class_<KingWrapper>("KingWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &KingWrapper::isValidMove, emscripten::allow_raw_pointers())
    ;
}