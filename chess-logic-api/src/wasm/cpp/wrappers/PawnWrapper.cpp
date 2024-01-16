#include "PawnWrapper.h"
#include "emscripten/bind.h"

PawnWrapper::PawnWrapper(PieceColor pieceColor, Square* currentSquare) : pawn(pieceColor, *currentSquare) {}

bool PawnWrapper::isValidMove(Board* board, Square* targetSquare) const {
  return pawn.isValidMove(*board, *targetSquare);
}

EMSCRIPTEN_BINDINGS(PawnWrapperModule) {
  emscripten::class_<PawnWrapper>("PawnWrapper")
    .constructor<PieceColor, Square*>()
    .function("isValidMove", &PawnWrapper::isValidMove, emscripten::allow_raw_pointers())
    ;
}