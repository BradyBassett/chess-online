#ifndef BITBOARDANDTEST_HPP
#define BITBOARDANDTEST_HPP

#include "../BitboardBinaryOperationsTest.hpp"

class BitboardANDTest : public BitboardBinaryOperationsTest
{
private:

protected:
	BitboardBinaryOperationsTestParam param;

public:
	BitboardANDTest();
	static std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> testCases;
};

#endif // BITBOARDANDTEST_HPP