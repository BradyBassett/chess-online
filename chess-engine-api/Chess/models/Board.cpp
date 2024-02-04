#include <stdexcept>
#include "Board.h"
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

Square& Board::getSquare(int rowIndex, int colIndex) {
	uint8_t boardSize = squares.size();
    if (rowIndex < 0 || rowIndex >= boardSize || colIndex < 0 || colIndex >= boardSize) {
        throw std::out_of_range("Square coordinates are out of range");
    }
    return squares[rowIndex][colIndex];
}

std::vector<std::vector<Square>> Board::getSquares() {
	return squares;
}

void Board::movePiece(Square& fromSquare, Square& toSquare) {
	std::shared_ptr<Piece> piece = fromSquare.getPiece();

	toSquare.setPiece(piece);
	fromSquare.setPiece(nullptr);
	piece->setHasMoved();
	piece->setCurrentPosition(toSquare.getPosition());
}