#include "BishopWrapper.h"
#include "emscripten/bind.h"

BishopWrapper::BishopWrapper(PieceColor pieceColor, Square* currentSquare) : bishop(pieceColor, *currentSquare) {}

bool BishopWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return bishop.isValidMove(*board, *targetSquare);
}

EMSCRIPTEN_BINDINGS(BishopWrapperModule) {
  emscripten::class_<BishopWrapper>("BishopWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &BishopWrapper::isValidMove, emscripten::allow_raw_pointers())
    ;
}