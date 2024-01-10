#include "Board.h"
#include "../utils/fenParser.h"

Board::Board(std::string fenPosition) {
	this->setStartingPosition(fenPosition);
}

void Board::setStartingPosition(std::string fenPosition) {
	squares.clear();

	std::vector<Square> parsedSquares = parseFenPosition(fenPosition); // TODO: implement parseFenPosition

	for (int i = 0; i < parsedSquares.size(); i += 8) {
		this->squares.push_back(std::vector<Square>(parsedSquares.begin() + i, parsedSquares.begin() + i + 8));
	}
}

Square Board::getSquare(int rowIndex, int colIndex) {
	return this->squares[rowIndex][colIndex];
}

// TODO : imoplement toJson method