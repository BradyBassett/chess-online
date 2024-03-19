#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Square.h"
#include "Bitboard.h"
#include "../enums/Side.h"
#include "../structs/Move.h"

class Rook;
class King;

class Board
{
private:
	std::vector<std::vector<Square>> squares;
	std::vector<std::shared_ptr<Rook>> rooks;
	std::vector<std::shared_ptr<King>> kings;
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

	bool isDigitFrom1To8(char c);

	std::vector<Square> parseFenPosition(std::string &fenPosition);

	void parseCastlingAvailability(const std::string &castling);

	void parseEnPassantTarget(const std::string &enPassant);

	void movePiece(Square &fromSquare, Square &toSquare, std::shared_ptr<Piece> piece);

	void initializeStartingPosition(std::string fenPosition);

	void initializeBitboards();

	void initializeAttackTables();

	Bitboard calculatePath(Position from, Position to, std::shared_ptr<Piece> piece);

	Bitboard calculateDiagonalPath(Position from, Position to);

	bool isDiagonal(Position from, Position to) const;

	Bitboard calculateOrthagonalPath(Position from, Position to);

	bool isOrthagonal(Position from, Position to) const;

public:
	Board(std::string fenPosition, std::string castlingAvailability, std::string enPassantTarget);

	Square &getSquare(int rowIndex, int colIndex);

	Square &getSquare(Position position);

	Square &getSquare(int squareNumber);

	std::vector<std::vector<Square>> getSquares();

	void setupMove(Move move);

	std::shared_ptr<Rook> getRook(Color color, Side side);

	std::shared_ptr<King> getKing(Color color);

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

	Bitboard (&getAttackTable(Color color, PieceType pieceType))[64];

	bool isPathClear(Position from, Position to, std::shared_ptr<Piece> piece);
};

#endif
