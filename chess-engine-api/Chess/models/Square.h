#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

class Piece;

class Square {
private:
	uint8_t rowIndex;
	uint8_t colIndex;
	std::shared_ptr<Piece> piece;

public:
	Square(int rowIndex, int colIndex, std::shared_ptr<Piece> piece = nullptr);

	Square(const Square& square) noexcept;

	uint8_t getRowIndex() const;

	uint8_t getColIndex() const;

	std::shared_ptr<Piece> getPiece() const;

	void setPiece(std::shared_ptr<Piece> piece);
};

#endif
