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
    {'r', [](Square square) {return std::make_shared<Rook>(PieceColor::Dark, square); }},
    {'n', [](Square square) {return std::make_shared<Knight>(PieceColor::Dark, square); }},
    {'b', [](Square square) {return std::make_shared<Bishop>(PieceColor::Dark, square); }},
    {'q', [](Square square) {return std::make_shared<Queen>(PieceColor::Dark, square); }},
    {'k', [](Square square) {return std::make_shared<King>(PieceColor::Dark, square); }},
    {'p', [](Square square) {return std::make_shared<Pawn>(PieceColor::Dark, square); }},
    {'R', [](Square square) {return std::make_shared<Rook>(PieceColor::Light, square); }},
    {'K', [](Square square) {return std::make_shared<Knight>(PieceColor::Light, square); }},
    {'B', [](Square square) {return std::make_shared<Bishop>(PieceColor::Light, square); }},
    {'Q', [](Square square) {return std::make_shared<Queen>(PieceColor::Light, square); }},
    {'K', [](Square square) {return std::make_shared<King>(PieceColor::Light, square); }},
    {'P', [](Square square) {return std::make_shared<Pawn>(PieceColor::Light, square); }}
  };

  for (char c : fenPosition) {
    if (c == '/') {
      if (rowIndex != 8 || colIndex >= 7) {
        throw std::invalid_argument("Invalid Fen Position");
      }
      rowIndex = 0;
      colIndex++;
    }
    else if (isDigitFrom1To8(c)) {
      for (uint8_t i = 0; i < c - '0'; i++) {
        squares.push_back(Square(rowIndex, colIndex));
        rowIndex++;
      }
    }
    else if (pieceTypes.count(c) == 0) {
      throw std::invalid_argument("Invalid Fen Position");
    }
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
