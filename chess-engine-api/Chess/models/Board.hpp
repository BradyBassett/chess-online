#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "Square.hpp"
#include "Bitboard.hpp"
#include "../enums/Side.hpp"
#include "../structs/Move.hpp"

class Rook;
class King;

class Board
{
private:
	std::vector<std::vector<Square>> squares;
	std::vector<std::shared_ptr<Rook>> rooks;
	std::vector<std::shared_ptr<King>> kings;
	bool canCastleKingside[2];
	bool canCastleQueenside[2];
	Square *enPassantTargetSquare;
	std::array<std::array<int, 6>, 2> pieceCount{};			 // [color][pieceType] = [white, black][pawns, knights, bishops, rooks, queens, king]
	std::array<std::array<Bitboard, 6>, 2> bitboards;		 // [color][pieceType] = [white, black][pawns, knights, bishops, rooks, queens, king]
	std::array<std::array<Bitboard, 64>, 2> pawnAttackTable; // [white, black]
	std::array<Bitboard, 64> knightAttackTable;
	std::array<Bitboard, 64> bishopAttackTable;
	std::array<Bitboard, 64> rookAttackTable;
	std::array<Bitboard, 64> queenAttackTable;
	std::array<Bitboard, 64> kingAttackTable;

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

	bool isCastleMove(Position from, Position to) const;

public:
	Board();

	Board(std::string fenPosition, std::string castlingAvailability, std::string enPassantTarget);

	Square &getSquare(int rowIndex, int colIndex);

	Square &getSquare(Position position);

	Square &getSquare(int squareNumber);

	std::vector<std::vector<Square>> getSquares();

	void setupMove(Move move);

	std::shared_ptr<Rook> getRook(Color color, Side side);

	std::vector<std::shared_ptr<Rook>> getRooks();

	std::shared_ptr<King> getKing(Color color);

	std::vector<std::shared_ptr<King>> getKings();

	Side getRookSide(Square square);

	Bitboard &getBitboard(Color color, PieceType pieceType);

	Bitboard getWhitePiecesBitboard();

	Bitboard getBlackPiecesBitboard();

	Bitboard getAllPiecesBitboard();

	bool getCanCastleKingside(Color color);

	bool getCanCastleQueenside(Color color);

	void setCanCastleKingside(bool value, Color color);

	void setCanCastleQueenside(bool value, Color color);

	void updateCastlingAvailability(Piece &fromPiece);

	Square *getEnPassantTargetSquare();

	void setEnPassantTargetSquare(Square *square);

	void updateEnPassantTargetSquare(Piece &fromPiece, Position from, Position to);

	Position convertStringToPosition(std::string position);

	std::string convertPositionToString(Position position);

	std::array<Bitboard, 64>& getAttackTable(Color color, PieceType pieceType);

	bool isPathClear(Position from, Position to, std::shared_ptr<Piece> piece);

	int getPieceCount(Color color, PieceType pieceType);

	void incrementPieceCount(Color color, PieceType pieceType);

	void decrementPieceCount(Color color, PieceType pieceType);
};

#endif // BOARD_HPP
