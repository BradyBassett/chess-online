#ifndef KINGGETPOTENTIALMOVESTEST_HPP
#define KINGGETPOTENTIALMOVESTEST_HPP

#include "../KingTest.hpp"

struct KingGetPotentialMovesTestParam
{
	Position currentPosition;
	Color color;
	Bitboard expectedMoves;
	bool hasMoved;
	bool canCastleKingside;
	bool canCastleQueenside;
};

class KingGetPotentialMovesTest : public KingTest, public ::testing::TestWithParam<std::pair<std::string, KingGetPotentialMovesTestParam>>
{
private:

protected:
	KingGetPotentialMovesTestParam param;

public:
	KingGetPotentialMovesTest();
	static std::vector<std::pair<std::string, KingGetPotentialMovesTestParam>> testCases;
};

#endif // KINGGETPOTENTIALMOVESTEST_HPP