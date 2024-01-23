#include "../models/Square.h"
#include <vector>

std::vector<Square> parseFenPosition(std::string& fenPosition);

bool isDigitFrom1To8(char c);

void parseFenActiveColor(std::string& fenActiveColor);

void parseFenCasteling(std::string& fenCasteling);

void parseFenEnPassant(std::string& fenEnPassant);

void parseFenHalfMoveClock(std::string& fenHalfMoveClock);