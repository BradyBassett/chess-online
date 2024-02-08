#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Square.h"
#include "../enums/Side.h"

class Rook;

class Board {
private:
	std::vector<std::vector<Square>> squares;

	std::vector<std::shared_ptr<Rook>> rooks;

	bool isDigitFrom1To8(char c);

	std::vector<Square> parseFenPosition(std::string& fenPosition);

public:
	Board(std::string fenPosition);

	void setStartingPosition(std::string fenPosition);

	Square& getSquare(int rowIndex, int colIndex);

	std::vector<std::vector<Square>> getSquares();

	void movePiece(Square& fromSquare, Square& toSquare);

	Rook& getRook(Color color, Side side);

	Side getRookSide(Square square);
};

#endif
