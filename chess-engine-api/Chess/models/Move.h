#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "../structs/Position.h"

class Move {
private:
	Position from;
	Position to;
	std::string promotion;

public:
	Move(Position from, Position to, std::string promotion);

	Position getFrom();

	Position getTo();

	std::string getPromotion();
};

#endif