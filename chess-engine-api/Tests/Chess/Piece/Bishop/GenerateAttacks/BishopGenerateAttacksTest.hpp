#ifndef BISHOPGENERATEATTACKSTEST_HPP
#define BISHOPGENERATEATTACKSTEST_HPP

#include "../BishopTest.hpp"

class BishopGenerateAttacksTest : public BishopTest, public ::testing::TestWithParam<std::pair<std::string, PieceGenerateAttacksTestParam>>
{
private:

protected:
	PieceGenerateAttacksTestParam param;

public:
	BishopGenerateAttacksTest();
	static std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> testCases;
};

#endif // BISHOPGENERATEATTACKSTEST_HPP