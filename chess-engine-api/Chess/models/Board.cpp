#include "Board.h"
#include <emscripten/bind.h>
#include "../utils/fenParser.h"

Board::Board(std::string fenPosition) {
	setStartingPosition(fenPosition);
}

void Board::setStartingPosition(std::string fenPosition) {
	squares.clear();

	std::vector<Square> parsedSquares = parseFenPosition(fenPosition);

	for (int i = 0; i < parsedSquares.size(); i += 8) {
		squares.push_back(std::vector<Square>(parsedSquares.begin() + i, parsedSquares.begin() + i + 8));
	}
}

Square Board::getSquare(int rowIndex, int colIndex) {
	return squares[rowIndex][colIndex];
}