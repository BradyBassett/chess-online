#ifndef QUEENGENERATEATTACKSTEST_HPP
#define QUEENGENERATEATTACKSTEST_HPP

#include "../QueenTest.hpp"

class QueenGenerateAttacksTest : public QueenTest, public ::testing::TestWithParam<std::pair<std::string, PieceGenerateAttacksTestParam>>
{
private:

protected:
	PieceGenerateAttacksTestParam param;

public:
	QueenGenerateAttacksTest();
	static std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> testCases;
};

#endif // QUEENGENERATEATTACKSTEST_HPP