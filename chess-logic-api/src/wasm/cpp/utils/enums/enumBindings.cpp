#include <emscripten/bind.h>
#include "PieceColor.h"
#include "PieceType.h"

EMSCRIPTEN_BINDINGS(PieceColorModule) {
  emscripten::enum_<PieceColor>("PieceColor")
    .value("White", PieceColor::Light)
    .value("Black", PieceColor::Dark)
    ;
}

EMSCRIPTEN_BINDINGS(PieceTypeModule) {
  emscripten::enum_<PieceType>("PieceType")
    .value("Bishop", PieceType::Bishop)
    .value("King", PieceType::King)
    .value("Knight", PieceType::Knight)
    .value("Pawn", PieceType::Pawn)
    .value("Queen", PieceType::Queen)
    .value("Rook", PieceType::Rook)
    ;    
}
