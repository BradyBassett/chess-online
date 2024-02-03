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
		{'r', [](Square square) {
			return std::make_shared<Rook>(Color::Black, square.getPosition());
		}},

		{'n', [](Square square) {
			return std::make_shared<Knight>(Color::Black, square.getPosition()); 
		}},
		{'b', [](Square square) {
			return std::make_shared<Bishop>(Color::Black, square.getPosition()); 
		}},
		{'q', [](Square square) {
			return std::make_shared<Queen>(Color::Black, square.getPosition()); 
		}},
		{'k', [](Square square) {
			return std::make_shared<King>(Color::Black, square.getPosition()); 
		}},
		{'p', [](Square square) {
			return std::make_shared<Pawn>(Color::Black, square.getPosition()); 
		}},
		{'R', [](Square square) {
			return std::make_shared<Rook>(Color::White, square.getPosition()); 
		}},
		{'N', [](Square square) {
			return std::make_shared<Knight>(Color::White, square.getPosition()); 
		}},
		{'B', [](Square square) {
			return std::make_shared<Bishop>(Color::White, square.getPosition()); 
		}},
		{'Q', [](Square square) {
			return std::make_shared<Queen>(Color::White, square.getPosition()); 
		}},
		{'K', [](Square square) {
			return std::make_shared<King>(Color::White, square.getPosition()); 
		}},
		{'P', [](Square square) {
			return std::make_shared<Pawn>(Color::White, square.getPosition()); 
		}}
	};

	for (char c : fenPosition) {
		Position position = {rowIndex, colIndex};
		// If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
		if (c == '/') {
			if (colIndex != 8 || rowIndex >= 7) {
				throw std::invalid_argument("Invalid Fen Position");
			}
			colIndex = 0;
			rowIndex++;
		}
		// if the character is any digit from 1-8 add empty squares to pieces (represented as null)
		else if (isDigitFrom1To8(c)) {
			for (int i = 0; i < c - '0'; i++) {
				squares.push_back(Square(position));
				colIndex++;
			}
		}
		// If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
		else if (pieceTypes.count(c) == 0) {
			throw std::invalid_argument("Invalid Fen Position");
		}
		// All remaining possible characters should represent pieces
		else {
			Square square = Square(position);
			std::shared_ptr<Piece> piece = pieceTypes[c](square);
			square.setPiece(piece);
			squares.push_back(square);
			colIndex++;
		}
	}

	return squares;
}

bool isDigitFrom1To8(char c) {
	std::string s(1, c);
	std::regex pattern("^[1-8]$");

	return std::regex_match(s, pattern);
}
