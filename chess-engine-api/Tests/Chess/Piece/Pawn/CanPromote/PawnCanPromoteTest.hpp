#ifndef PAWNCANPROMOTETEST_HPP
#define PAWNCANPROMOTETEST_HPP

#include "../PawnTest.hpp"

struct PawnCanPromoteTestParam
{
	Color color;
	Position currentPosition;
	bool expectedResult;
};

class PawnCanPromoteTest : public PawnTest, public ::testing::TestWithParam<std::pair<std::string, PawnCanPromoteTestParam>>
{
private:

protected:
	PawnCanPromoteTestParam param;

public:
	PawnCanPromoteTest();
	static std::vector<std::pair<std::string, PawnCanPromoteTestParam>> testCases;
};

#endif // PAWNCANPROMOTETEST_HPP