#include "fenParser.h"
#include <map>
#include <regex>
#include "../models/Rook.h"
#include "../models/Knight.h"
#include "../models/Bishop.h"
#include "../models/Queen.h"
#include "../models/King.h"
#include "../models/Pawn.h"

std::vector<Square> parseFenPosition(std::string& fenPosition) {
	std::vector<Square> squares;

	uint8_t rowIndex = 0;
	uint8_t colIndex = 0;

	std::map<char, std::function<std::shared_ptr<Piece>(Square)>> pieceTypes = {
		{'r', [](Square square) {return std::make_shared<Rook>(Color::Black, square); }},
		{'n', [](Square square) {return std::make_shared<Knight>(Color::Black, square); }},
		{'b', [](Square square) {return std::make_shared<Bishop>(Color::Black, square); }},
		{'q', [](Square square) {return std::make_shared<Queen>(Color::Black, square); }},
		{'k', [](Square square) {return std::make_shared<King>(Color::Black, square); }},
		{'p', [](Square square) {return std::make_shared<Pawn>(Color::Black, square); }},
		{'R', [](Square square) {return std::make_shared<Rook>(Color::White, square); }},
		{'N', [](Square square) {return std::make_shared<Knight>(Color::White, square); }},
		{'B', [](Square square) {return std::make_shared<Bishop>(Color::White, square); }},
		{'Q', [](Square square) {return std::make_shared<Queen>(Color::White, square); }},
		{'K', [](Square square) {return std::make_shared<King>(Color::White, square); }},
		{'P', [](Square square) {return std::make_shared<Pawn>(Color::White, square); }}
	};

	for (char c : fenPosition) {
		// If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
		if (c == '/') {
			if (rowIndex != 8 || colIndex >= 7) {
				throw std::invalid_argument("Invalid Fen Position");
			}
			rowIndex = 0;
			colIndex++;
		}
		// if the character is any digit from 1-8 add empty squares to pieces (represented as null)
		else if (isDigitFrom1To8(c)) {
			for (uint8_t i = 0; i < c - '0'; i++) {
				squares.push_back(Square(rowIndex, colIndex));
				rowIndex++;
			}
		}
		// If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
		else if (pieceTypes.count(c) == 0) {
			throw std::invalid_argument("Invalid Fen Position");
		}
		// All remaining possible characters should represent pieces
		else {
			Square square = Square(rowIndex, colIndex);
			std::shared_ptr<Piece> piece = pieceTypes[c](square);
			square.setPiece(piece);
			squares.push_back(square);
			rowIndex++;
		}
	}

	return squares;
}

bool isDigitFrom1To8(char c) {
	std::string s(1, c);
	std::regex pattern("^[1-8]$");

	return std::regex_match(s, pattern);
}
