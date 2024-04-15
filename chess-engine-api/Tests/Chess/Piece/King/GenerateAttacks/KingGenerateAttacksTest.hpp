#ifndef KINGGENERATEATTACKSTEST_HPP
#define KINGGENERATEATTACKSTEST_HPP

#include "../KingTest.hpp"

class KingGenerateAttacksTest : public KingTest, public ::testing::TestWithParam<std::pair<std::string, PieceGenerateAttacksTestParam>>
{
private:

protected:
	PieceGenerateAttacksTestParam param;

public:
	KingGenerateAttacksTest();
	static std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> testCases;

};

#endif // KINGGENERATEATTACKSTEST_HPP