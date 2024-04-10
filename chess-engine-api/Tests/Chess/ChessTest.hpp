#ifndef CHESSTEST_HPP
#define CHESSTEST_HPP

#include <map>
#include <string>
#include "../Tests.hpp"
#include "../../Chess/enums/PieceType.hpp"
#include "../../Chess/enums/Color.hpp"

class ChessTest : public Tests
{
private:

protected:

public:
	std::map<PieceType, std::string> pieceTypeMap = {
		{PieceType::Pawn, "Pawn"},
		{PieceType::Knight, "Knight"},
		{PieceType::Bishop, "Bishop"},
		{PieceType::Rook, "Rook"},
		{PieceType::Queen, "Queen"},
		{PieceType::King, "King"}
	};

	std::map<Color, std::string> colorMap = {
		{Color::White, "White"},
		{Color::Black, "Black"}
	};
};

#endif // CHESSTEST_HPP