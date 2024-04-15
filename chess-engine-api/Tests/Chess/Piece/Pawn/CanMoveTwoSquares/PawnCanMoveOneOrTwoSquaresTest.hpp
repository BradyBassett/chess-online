#ifndef PAWNCANMOVEONEORTWOSQUARESTEST_HPP
#define PAWNCANMOVEONEORTWOSQUARESTEST_HPP

#include "../PawnTest.hpp"

struct PawnCanMoveOneOrTwoSquaresTestParam
{
	Color color;
	Position currentPosition;
	Position targetPosition;
	bool hasMoved;
	bool expectedResult;
};

class PawnCanMoveOneOrTwoSquaresTest : public PawnTest, public ::testing::TestWithParam<std::pair<std::string, PawnCanMoveOneOrTwoSquaresTestParam>>
{
private:

protected:
	PawnCanMoveOneOrTwoSquaresTestParam param;

public:
	PawnCanMoveOneOrTwoSquaresTest();
	static std::vector<std::pair<std::string, PawnCanMoveOneOrTwoSquaresTestParam>> testCases;
};

#endif // PAWNCANMOVEONEORTWOSQUARESTEST_HPP