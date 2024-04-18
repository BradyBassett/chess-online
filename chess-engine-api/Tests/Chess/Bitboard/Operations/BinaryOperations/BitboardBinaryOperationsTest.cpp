#include "BitboardBinaryOperationsTest.hpp"

BitboardBinaryOperationsTestParam BitboardBinaryOperationsTest::generateRandomBitwiseTestParam(std::function<uint64_t(uint64_t, uint64_t)> operation, uint64_t value1, bool useRandomValue1) {
	uint64_t random_value1 = useRandomValue1 ? Tests::generateRandomUint64Value() : value1;
	uint64_t random_value2 = Tests::generateRandomUint64Value();
	uint64_t result_value = operation(random_value1, random_value2);

	return BitboardBinaryOperationsTestParam{Bitboard(random_value1), Bitboard(random_value2), Bitboard(result_value)};
}

BitboardBinaryOperationsTestParam BitboardBinaryOperationsTest::generateRandomBitShiftTestParam(std::function<uint64_t(uint64_t, uint64_t)> operation, uint64_t value1, bool useRandomValue1) {
	uint64_t random_value1 = useRandomValue1 ? Tests::generateRandomUint64Value() : value1;
	uint64_t random_value2 = Tests::generateRandomUint64Value(0, 63);
	uint64_t result_value = operation(random_value1, random_value2);

	return BitboardBinaryOperationsTestParam{Bitboard(random_value1), random_value2, Bitboard(result_value)};
}