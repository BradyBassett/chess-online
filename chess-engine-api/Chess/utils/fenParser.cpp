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
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Rook>(Color::Black, squarePtr);
		}},

		{'n', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Knight>(Color::Black, squarePtr); 
		}},
		{'b', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Bishop>(Color::Black, squarePtr); 
		}},
		{'q', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Queen>(Color::Black, squarePtr); 
		}},
		{'k', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<King>(Color::Black, squarePtr); 
		}},
		{'p', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Pawn>(Color::Black, squarePtr); 
		}},
		{'R', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Rook>(Color::White, squarePtr); 
		}},
		{'N', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Knight>(Color::White, squarePtr); 
		}},
		{'B', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Bishop>(Color::White, squarePtr); 
		}},
		{'Q', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Queen>(Color::White, squarePtr); 
		}},
		{'K', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<King>(Color::White, squarePtr); 
		}},
		{'P', [](Square square) {
			auto squarePtr = std::make_shared<Square>(square);
			return std::make_shared<Pawn>(Color::White, squarePtr); 
		}}
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
			for (int i = 0; i < c - '0'; i++) {
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
