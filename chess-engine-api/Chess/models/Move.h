#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
private:
	std::string from;
	std::string to;
	char promotion;

public:
	Move(std::string from, std::string to, char promotion = ' ');

	std::string getFrom();

	std::string getTo();

	char getPromotion();

	std::string toString();
};

#endif