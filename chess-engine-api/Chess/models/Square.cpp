#include "Piece.h"
#include "Square.h"

Square::Square(Position position, std::shared_ptr<Piece> piece)
	: position(position), piece(std::move(piece)) {
}

Position Square::getPosition() const {
	return position;
}

std::shared_ptr<Piece> Square::getPiece() const {
	return piece;
}

void Square::setPiece(std::shared_ptr<Piece> piece) {
	this->piece = piece;
}
