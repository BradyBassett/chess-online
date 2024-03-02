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
	Bitboard bitboards[2][6]; // [color][pieceType] = [white, black][pawns, knights, bishops, rooks, queens, king]
	// TODO - Add methods to generate attack tables for each piece using something called incremental updates after the following
	// TODO - Conditions are met: 1. A piece is moved 2. A piece is captured 3. A piece is Promoted 4. On initialization 5. On castling
	// TODO - 6. on en passant (Research incremental updates)

	bool isDigitFrom1To8(char c);

	std::vector<Square> parseFenPosition(std::string &fenPosition);

	void movePiece(Square &fromSquare, Square &toSquare, std::shared_ptr<Piece> piece);

	void initializeStartingPosition(std::string fenPosition);

	void initializeBitboards(std::string fenPosition);

public:
	Board(std::string fenPosition);

	Square &getSquare(int rowIndex, int colIndex);

	Square &getSquare(Position position);

	std::vector<std::vector<Square>> getSquares();

	void setupMove(Move move);

	std::shared_ptr<Rook> getRook(Color color, Side side);

	Side getRookSide(Square square);

	Bitboard &getBitboard(Color color, PieceType pieceType);

	Bitboard getWhitePiecesBitboard();

	Bitboard getBlackPiecesBitboard();

	Bitboard getAllPiecesBitboard();
};

#endif
