#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <memory>
#include "../structs/Position.hpp"

class Piece;

class Square
{
private:
	Position position;
	std::shared_ptr<Piece> piece;

public:
	Square(Position position, std::shared_ptr<Piece> piece = nullptr);

	Position getPosition() const;

	std::shared_ptr<Piece> getPiece() const;

	void setPiece(std::shared_ptr<Piece> piece);
};

#include "Piece.hpp"

#endif // SQUARE_HPP
