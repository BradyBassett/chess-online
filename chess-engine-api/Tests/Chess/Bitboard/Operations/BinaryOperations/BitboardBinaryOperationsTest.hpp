#ifndef BITBOARBINARYDOPERATIONSTEST_HPP
#define BITBOARBINARYDOPERATIONSTEST_HPP

#include "../../BitboardTest.hpp"

struct BitboardBinaryOperationsTestParam
{
	Bitboard initialBitboard;
	std::variant<Bitboard, uint64_t> operationParameter;
	Bitboard expectedResult;
};

class BitboardBinaryOperationsTest : public BitboardTest, public ::testing::TestWithParam<std::pair<std::string, BitboardBinaryOperationsTestParam>>
{
private:

protected:

public:
	static BitboardBinaryOperationsTestParam generateRandomBitwiseTestParam(std::function<uint64_t(uint64_t, uint64_t)> operation, uint64_t value1 = 0ULL, bool useRandomValue1 = true);

	static BitboardBinaryOperationsTestParam generateRandomBitShiftTestParam(std::function<uint64_t(uint64_t, uint64_t)> operation, uint64_t value1 = 0ULL, bool useRandomValue1 = true);
};

#endif // BITBOARBINARYDOPERATIONSTEST_HPPs