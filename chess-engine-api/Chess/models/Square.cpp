#include "Piece.h"
#include "Square.h"

Square::Square(int rowIndex, int colIndex, std::shared_ptr<Piece> piece)
	: rowIndex(rowIndex), colIndex(colIndex), piece(std::move(piece)) {
}

Square::Square(const Square& square) noexcept
	: rowIndex(square.rowIndex), colIndex(square.colIndex), piece(square.piece) {
}

bool Square::operator==(const Square& other) const {
    return rowIndex == other.rowIndex && colIndex == other.colIndex;
}

uint8_t Square::getRowIndex() const {
	return rowIndex;
}

uint8_t Square::getColIndex() const {
	return colIndex;
}

std::shared_ptr<Piece> Square::getPiece() const {
	return piece;
}

void Square::setPiece(std::shared_ptr<Piece> piece) {
	this->piece = piece;
}
