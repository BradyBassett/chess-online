#ifndef PAWNCANMOVEONESQUARETEST_HPP
#define PAWNCANMOVEONESQUARETEST_HPP

#include "../PawnTest.hpp"

struct PawnCanMoveOneSquareTestParam
{
	Color color;
	Position currentPosition;
	Position targetPosition;
	bool expectedResult;
};

class PawnCanMoveOneSquareTest : public PawnTest, public ::testing::TestWithParam<std::pair<std::string, PawnCanMoveOneSquareTestParam>>
{
private:

protected:
	PawnCanMoveOneSquareTestParam param;

public:
	PawnCanMoveOneSquareTest();
	static std::vector<std::pair<std::string, PawnCanMoveOneSquareTestParam>> testCases;
};

#endif // PAWNCANMOVEONESQUARETEST_HPP