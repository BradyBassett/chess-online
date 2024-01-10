#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include "Piece.h"

class Square {
public:
	uint8_t rowIndex;
	uint8_t colIndex;
	std::shared_ptr<Piece> piece;

	Square(int rowIndex, int colIndex, std::shared_ptr<Piece> piece = nullptr);

	Square(const Square& square);
};

#endif
