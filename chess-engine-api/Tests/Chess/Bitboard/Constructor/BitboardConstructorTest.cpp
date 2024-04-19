#include "BitboardConstructorTest.hpp"

TEST(BitboardConstructorTest, constructorPosition)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Position position = {i, j};
			uint64_t expectedValue = 0x1ULL << (i * 8 + j);
			Bitboard bitboard(position);

			ASSERT_EQ(bitboard.getValue(), expectedValue);
		}
	}
}

TEST(BitboardConstructorTest, constructorValue)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t value = 0x1ULL << i;
		Bitboard bitboard(value);

		ASSERT_EQ(bitboard.getValue(), value);
	}
}