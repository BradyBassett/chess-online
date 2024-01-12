#ifndef SQUARE_H
#define SQUARE_H

#include "Piece.h"

class Square {
private:
	uint8_t rowIndex;
	uint8_t colIndex;
	std::shared_ptr<Piece> piece;

public:
	Square(int rowIndex, int colIndex, std::shared_ptr<Piece> piece = nullptr);

	Square(const Square& square);

	uint8_t getRowIndex() const;

	uint8_t getColIndex() const;

	std::shared_ptr<Piece> getPiece() const;

	void setPiece(std::shared_ptr<Piece> piece);
};

#endif
