#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
private:
	int fromRow;
	int fromCol;
	int toRow;
	int toCol;
	char promotion;

public:
	Move(int fromRow, int fromCol, int toRow, int toCol, char promotion = ' ');

	int getFromRow();

	int getFromCol();

	int getToRow();

	int getToCol();

	char getPromotion();

	std::string toString();
};

#endif