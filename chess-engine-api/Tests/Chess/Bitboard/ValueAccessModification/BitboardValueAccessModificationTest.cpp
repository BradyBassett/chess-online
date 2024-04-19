#include "BitboardValueAccessModificationTest.hpp"

TEST_F(BitboardValueAccessModificationTest, setAndGetValue_100)
{
	Bitboard bitboard;

	for (int index = 0; index < 100; index++)
	{
		uint64_t value = generateRandomUint64Value();

		bitboard.setValue(value);

		ASSERT_EQ(bitboard.getValue(), value);
	}
}