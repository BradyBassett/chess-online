#ifndef BITBOARDORTEST_HPP
#define BITBOARDORTEST_HPP

#include "../BitboardBinaryOperationsTest.hpp"

class BitboardORTest : public BitboardBinaryOperationsTest
{
private:

protected:
	BitboardBinaryOperationsTestParam param;

public:
	BitboardORTest();
	static std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> testCases;
};

#endif // BITBOARDORTEST_HPP