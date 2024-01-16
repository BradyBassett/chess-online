#include "SquareWrapper.h"
#include "emscripten/bind.h"
#include "../models/Square.h"

SquareWrapper::SquareWrapper(int rowIndex, int colIndex, PieceWrapper* pieceWrapper) 
  : square(rowIndex, colIndex, std::make_shared<Piece>(pieceWrapper->getPiece())) {}

uint8_t SquareWrapper::getRowIndex() const {
  return square.getRowIndex();
}

uint8_t SquareWrapper::getColIndex() const {
  return square.getColIndex();
}

PieceWrapper* SquareWrapper::getPiece() const {
  Piece piece = *square.getPiece();

  return new PieceWrapper(piece.getPieceColor(), &piece.getCurrentSquare());
}

void SquareWrapper::setPiece(PieceWrapper* pieceWrapper) {
  square.setPiece(std::make_shared<Piece>(pieceWrapper->getPiece()));
}

EMSCRIPTEN_BINDINGS(SquareWrapperModule) {
  emscripten::class_<SquareWrapper>("SquareWrapper")
    .constructor<int, int, PieceWrapper*>()
    .function("getRowIndex", &SquareWrapper::getRowIndex)
    .function("getColIndex", &SquareWrapper::getColIndex)
    .function("getPiece", &SquareWrapper::getPiece, emscripten::allow_raw_pointers())
    .function("setPiece", &SquareWrapper::setPiece, emscripten::allow_raw_pointers())
    ;
}