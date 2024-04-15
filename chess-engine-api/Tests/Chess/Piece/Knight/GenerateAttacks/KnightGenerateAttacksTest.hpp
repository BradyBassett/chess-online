#ifndef KNIGHTGENERATEATTACKSTEST_HPP
#define KNIGHTGENERATEATTACKSTEST_HPP

#include "../KnightTest.hpp"

class KnightGenerateAttacksTest : public KnightTest, public ::testing::TestWithParam<std::pair<std::string, PieceGenerateAttacksTestParam>>
{
private:

protected:
	PieceGenerateAttacksTestParam param;

public:
	KnightGenerateAttacksTest();
	static std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> testCases;
};

#endif // KNIGHTGENERATEATTACKSTEST_HPP