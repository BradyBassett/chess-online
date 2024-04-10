#ifndef ChessTest_H
#define ChessTest_H

#include <map>
#include <string>
#include "../Tests.h"
#include "../../Chess/enums/PieceType.h"
#include "../../Chess/enums/Color.h"

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

#endif // ChessTest_H