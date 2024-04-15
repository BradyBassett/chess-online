#ifndef PAWNGETPOTENTIALMOVESTEST_HPP
#define PAWNGETPOTENTIALMOVESTEST_HPP

#include "../PawnTest.hpp"

struct PawnGetPotentialMovesTestParam
{
	Position currentPosition;
	Color color;
	Bitboard expectedMoves;
	bool hasMoved;
};

class PawnGetPotentialMovesTest : public PawnTest, public ::testing::TestWithParam<std::pair<std::string, PawnGetPotentialMovesTestParam>>
{
private:

protected:
	PawnGetPotentialMovesTestParam param;

public:
	PawnGetPotentialMovesTest();
	static std::vector<std::pair<std::string, PawnGetPotentialMovesTestParam>> testCases;
};

#endif // PAWNGETPOTENTIALMOVESTEST_HPP