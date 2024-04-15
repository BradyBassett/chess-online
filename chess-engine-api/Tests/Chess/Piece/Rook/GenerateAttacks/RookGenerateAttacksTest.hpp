#ifndef ROOKGENERATEATTACKSTEST_HPP
#define ROOKGENERATEATTACKSTEST_HPP

#include "../RookTest.hpp"

class RookGenerateAttacksTest : public RookTest, public ::testing::TestWithParam<std::pair<std::string, PieceGenerateAttacksTestParam>>
{
private:

protected:
	PieceGenerateAttacksTestParam param;

public:
	RookGenerateAttacksTest();
	static std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> testCases;
};

#endif // ROOKGENERATEATTACKSTEST_HPP