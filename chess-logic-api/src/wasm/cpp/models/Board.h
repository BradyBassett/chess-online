#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Square.h"

class Board {
private:
	std::vector<std::vector<Square>> squares;

public:
	Board(std::string fenPosition);

	void setStartingPosition(std::string fenPosition);

	Square getSquare(int rowIndex, int colIndex);

	// TODO : figure out how to return an array of squares in json format
};

#endif
