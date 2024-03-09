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
	bool whiteCanCastleKingside;
	bool whiteCanCastleQueenside;
	bool blackCanCastleKingside;
	bool blackCanCastleQueenside;
	Square *enPassantTargetSquare;
	Bitboard bitboards[2][6];		 // [color][pieceType] = [white, black][pawns, knights, bishops, rooks, queens, king]
	Bitboard pawnAttackTable[2][64]; // [white, black]
	Bitboard knightAttackTable[64];
	Bitboard bishopAttackTable[64];
	Bitboard rookAttackTable[64];
	Bitboard queenAttackTable[64];
	Bitboard kingAttackTable[64];
	// TODO - Add methods to generate attack tables for each piece using something called incremental updates after the following
	// TODO - Conditions are met: 1. A piece is moved 2. A piece is captured 3. A piece is Promoted 4. On initialization 5. On castling
	// TODO - 6. on en passant (Research incremental updates)

	bool isDigitFrom1To8(char c);

	std::vector<Square> parseFenPosition(std::string &fenPosition);

	void parseCastlingAvailability(const std::string &castling);

	void parseEnPassantTarget(const std::string &enPassant);

	void movePiece(Square &fromSquare, Square &toSquare, std::shared_ptr<Piece> piece);

	void initializeStartingPosition(std::string fenPosition);

	void initializeBitboards();

	void initializeAttackTables();

public:
	Board(std::string fenPosition, std::string castlingAvailability, std::string enPassantTarget);

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

	bool getWhiteCanCastleKingside();

	bool getWhiteCanCastleQueenside();

	bool getBlackCanCastleKingside();

	bool getBlackCanCastleQueenside();

	void setWhiteCanCastleKingside(bool value);

	void setWhiteCanCastleQueenside(bool value);

	void setBlackCanCastleKingside(bool value);

	void setBlackCanCastleQueenside(bool value);

	void updateCastlingAvailability(Piece &fromPiece);

	Square *getEnPassantTargetSquare();

	void setEnPassantTargetSquare(Square *square);

	void updateEnPassantTargetSquare(Piece &fromPiece, Position from, Position to);

	Position convertStringToPosition(std::string position);
};

#endif
