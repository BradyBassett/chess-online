#ifndef PIECETEST_HPP
#define PIECETEST_HPP

#include "../ChessTest.hpp"
#include "../../../Chess/models/Bitboard.hpp"

struct PieceGenerateAttacksTestParam
{
	Position currentPosition;
	Color color;
	Bitboard expectedAttacks;
};

class PieceTest : public ChessTest
{
private:

protected:

public:

};

#endif // PIECETEST_HPP