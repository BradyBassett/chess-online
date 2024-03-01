#include "Board.h"
#include <stdexcept>
#include <map>
#include <regex>
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

bool Board::isDigitFrom1To8(char c)
{
	std::string s(1, c);
	std::regex pattern("^[1-8]$");

	return std::regex_match(s, pattern);
}

// TODO - I need to dynamically set the bits for each piece's bitboard when parsing the pieces from the fen position
// Whenever a piece appears I determine its color and type enums, from that I can access the specific bitboard by using the enum values as the indexes

std::vector<Square> Board::parseFenPosition(std::string &fenPosition)
{
	std::vector<Square> squares;

	uint8_t rowIndex = 0;
	uint8_t colIndex = 0;

	std::map<char, std::function<std::shared_ptr<Piece>(Square)>> pieceTypes = {
		{'r', [this](Square square)
		 {
			 std::shared_ptr<Rook> rook = std::make_shared<Rook>(Color::Black, square.getPosition(), getRookSide(square));
			 rooks.push_back(rook);
			 return rook;
		 }},
		{'n', [](Square square)
		 {
			 return std::make_shared<Knight>(Color::Black, square.getPosition());
		 }},
		{'b', [](Square square)
		 {
			 return std::make_shared<Bishop>(Color::Black, square.getPosition());
		 }},
		{'q', [](Square square)
		 {
			 return std::make_shared<Queen>(Color::Black, square.getPosition());
		 }},
		{'k', [](Square square)
		 {
			 return std::make_shared<King>(Color::Black, square.getPosition());
		 }},
		{'p', [](Square square)
		 {
			 return std::make_shared<Pawn>(Color::Black, square.getPosition());
		 }},
		{'R', [this](Square square)
		 {
			 std::shared_ptr<Rook> rook = std::make_shared<Rook>(Color::White, square.getPosition(), getRookSide(square));
			 rooks.push_back(rook);
			 return rook;
		 }},
		{'N', [](Square square)
		 {
			 return std::make_shared<Knight>(Color::White, square.getPosition());
		 }},
		{'B', [](Square square)
		 {
			 return std::make_shared<Bishop>(Color::White, square.getPosition());
		 }},
		{'Q', [](Square square)
		 {
			 return std::make_shared<Queen>(Color::White, square.getPosition());
		 }},
		{'K', [](Square square)
		 {
			 return std::make_shared<King>(Color::White, square.getPosition());
		 }},
		{'P', [](Square square)
		 {
			 return std::make_shared<Pawn>(Color::White, square.getPosition());
		 }}};

	for (char c : fenPosition)
	{
		// If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
		if (c == '/')
		{
			if (colIndex != 8 || rowIndex >= 7)
			{
				throw std::invalid_argument("Invalid Fen Position");
			}
			colIndex = 0;
			rowIndex++;
		}
		// if the character is any digit from 1-8 add empty squares to pieces (represented as null)
		else if (isDigitFrom1To8(c))
		{
			for (int i = 0; i < c - '0'; i++)
			{
				squares.push_back(Square({rowIndex, colIndex}));
				colIndex++;
			}
		}
		// If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
		else if (pieceTypes.count(c) == 0)
		{
			throw std::invalid_argument("Invalid Fen Position");
		}
		// All remaining possible characters should represent pieces
		else
		{
			Square square = Square({rowIndex, colIndex});
			std::shared_ptr<Piece> piece = pieceTypes[c](square);
			square.setPiece(piece);
			squares.push_back(square);
			colIndex++;
		}
	}

	return squares;
}

void Board::movePiece(Square &fromSquare, Square &toSquare, std::shared_ptr<Piece> piece)
{
	Bitboard &pieceBitboard = getBitboard(piece->getPieceColor(), piece->getPieceType());
	pieceBitboard.clearBit(fromSquare.getPosition());
	pieceBitboard.setBit(toSquare.getPosition());
	toSquare.setPiece(piece);
	fromSquare.setPiece(nullptr);
	piece->setHasMoved();
	piece->setCurrentPosition(toSquare.getPosition());
}

void Board::initializeStartingPosition(std::string fenPosition)
{
	squares.clear();

	std::vector<Square> parsedSquares = parseFenPosition(fenPosition);

	for (int i = 0; i < parsedSquares.size(); i += 8)
	{
		squares.push_back(std::vector<Square>(parsedSquares.begin() + i, parsedSquares.begin() + i + 8));
	}
}

void Board::initializeBitboards(std::string fenPosition)
{
	// initialize bitboards to 0
	// TODO - set the actual bitboard values in the parseFenPosition method
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			bitboards[i][j].setValue(0ULL);
		}
	}
}

Board::Board(std::string fenPosition)
{
	initializeStartingPosition(fenPosition);
	initializeBitboards(fenPosition);
}

// TODO - Replace the parameters with a single Position object
Square &Board::getSquare(int rowIndex, int colIndex)
{
	uint8_t boardSize = squares.size();
	if (rowIndex < 0 || rowIndex >= boardSize || colIndex < 0 || colIndex >= boardSize)
	{
		throw std::out_of_range("Square coordinates are out of range");
	}
	return squares[rowIndex][colIndex];
}

std::vector<std::vector<Square>> Board::getSquares()
{
	return squares;
}

void Board::setupMove(Move move)
{
	Square &fromSquare = getSquare(move.from.row, move.from.col);
	Square &toSquare = getSquare(move.to.row, move.to.col);
	std::shared_ptr<Piece> piece = fromSquare.getPiece();

	// If the move is a castling move, move the rook as well
	if (piece->getPieceType() == PieceType::King && piece->getHasMoved() == false)
	{
		if (move.flags.test(static_cast<int>(MoveFlag::KingsideCastling)))
		{
			std::shared_ptr<Rook> rook = getRook(piece->getPieceColor(), Side::KingSide);
			Square &rookFromSquare = getSquare(move.from.row, 7);
			Square &rookToSquare = getSquare(move.to.row, 5);
			movePiece(rookFromSquare, rookToSquare, rook);
		}
		else if (move.flags.test(static_cast<int>(MoveFlag::QueensideCastling)))
		{
			std::shared_ptr<Rook> rook = getRook(piece->getPieceColor(), Side::QueenSide);
			Square &rookFromSquare = getSquare(move.from.row, 0);
			Square &rookToSquare = getSquare(move.to.row, 3);
			movePiece(rookFromSquare, rookToSquare, rook);
		}
	}

	// If the move is an en passant move, remove the captured pawn
	if (move.flags.test(static_cast<int>(MoveFlag::EnPassant)))
	{
		// remove from board and bitboard
		Square &capturedPawnSquare = getSquare(move.from.row, move.to.col);
		capturedPawnSquare.setPiece(nullptr);
		Bitboard &capturedPawnBitboard = getBitboard(piece->getPieceColor() == Color::White ? Color::Black : Color::White, PieceType::Pawn);
		capturedPawnBitboard.clearBit(capturedPawnSquare.getPosition());
	}

	movePiece(fromSquare, toSquare, piece);
}

std::shared_ptr<Rook> Board::getRook(Color color, Side side)
{
	for (std::shared_ptr<Rook> rook : rooks)
	{
		if (rook->getPieceColor() == color && rook->getSide() == side)
		{
			return rook;
		}
	}

	throw std::invalid_argument("No rook found");
}

Side Board::getRookSide(Square square)
{
	return (square.getPosition().col == 0) ? Side::QueenSide : Side::KingSide;
}

Bitboard &Board::getBitboard(Color color, PieceType pieceType)
{
	return bitboards[static_cast<int>(color)][static_cast<int>(pieceType)];
}

Bitboard Board::getWhitePiecesBitboard()
{
	return bitboards[0][0] | bitboards[0][1] | bitboards[0][2] | bitboards[0][3] | bitboards[0][4] | bitboards[0][5];
}

Bitboard Board::getBlackPiecesBitboard()
{
	return bitboards[1][0] | bitboards[1][1] | bitboards[1][2] | bitboards[1][3] | bitboards[1][4] | bitboards[1][5];
}

Bitboard Board::getAllPiecesBitboard()
{
	return getWhitePiecesBitboard() | getBlackPiecesBitboard();
}