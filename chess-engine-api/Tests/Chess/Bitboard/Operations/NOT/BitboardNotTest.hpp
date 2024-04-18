#ifndef BITBOARDNOTTEST_HPP
#define BITBOARDNOTTEST_HPP

#include "../../BitboardTest.hpp"

struct BitboardNotTestParam
{
	Bitboard initialBitboard;
	Bitboard expectedResult;
};

class BitboardNotTest : public BitboardTest, public ::testing::TestWithParam<std::pair<std::string, BitboardNotTestParam>>
{
private:

protected:
	BitboardNotTestParam param;

public:
	BitboardNotTest();
	static std::vector<std::pair<std::string, BitboardNotTestParam>> testCases;
};

#endif // BITBOARDNOTTEST_HPP