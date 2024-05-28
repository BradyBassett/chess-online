#include "Piece.hpp"
#include "Square.hpp"

Square::Square(Position position, std::shared_ptr<Piece> piece)
	: position(position), piece(std::move(piece))
{
}

Square::Square(const Square &other)
	: position(other.position)
{
	if (other.piece)
	{
		piece = std::make_shared<Piece>(*other.piece);
	}
}

Position Square::getPosition() const
{
	return position;
}

std::shared_ptr<Piece> Square::getPiece() const
{
	return piece;
}

void Square::setPiece(std::shared_ptr<Piece> piece)
{
	this->piece = piece;
}
