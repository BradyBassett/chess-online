#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include "../structs/Position.h"

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

#include "Piece.h"

#endif
