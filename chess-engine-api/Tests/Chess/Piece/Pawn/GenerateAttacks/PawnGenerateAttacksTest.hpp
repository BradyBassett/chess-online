#ifndef PAWNGENERATEATTACKSTEST_HPP
#define PAWNGENERATEATTACKSTEST_HPP

#include "../PawnTest.hpp"

class PawnGenerateAttacksTest : public PawnTest, public ::testing::TestWithParam<std::pair<std::string, PieceGenerateAttacksTestParam>>
{
private:

protected:
	PieceGenerateAttacksTestParam param;

public:
	PawnGenerateAttacksTest();
	static std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> testCases;
};

#endif // PAWNGENERATEATTACKSTEST_HPP