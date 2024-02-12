#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Square.h"
#include "Bitboard.h"
#include "../enums/Side.h"
#include "../structs/Move.h"

class Rook;

class Board
{
private:
	std::vector<std::vector<Square>> squares;
	std::vector<std::shared_ptr<Rook>> rooks;
	Bitboard bitboard;

	bool isDigitFrom1To8(char c);

	std::vector<Square> parseFenPosition(std::string &fenPosition);

	void movePiece(Square &fromSquare, Square &toSquare, std::shared_ptr<Piece> piece);

public:
	Board(std::string fenPosition);

	void setStartingPosition(std::string fenPosition);

	Square &getSquare(int rowIndex, int colIndex);

	std::vector<std::vector<Square>> getSquares();

	void setupMove(Move move);

	std::shared_ptr<Rook> getRook(Color color, Side side);

	Side getRookSide(Square square);
};

#endif
