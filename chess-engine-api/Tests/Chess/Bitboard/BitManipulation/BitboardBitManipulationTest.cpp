#include "BitboardBitManipulationTest.hpp"

TEST_F(BitboardBitManipulationTest, setAndClearBit_getBitIndex)
{
	Bitboard bitboard;

	for (int index = 0; index < 64; index++)
	{
		Position position = {index / 8, index % 8};

		bitboard.setBit(position);

		ASSERT_TRUE(bitboard.getBit(index));

		bitboard.clearBit(position);

		ASSERT_FALSE(bitboard.getBit(index));
	}
}

TEST_F(BitboardBitManipulationTest, setAndClearBit_getBitPosition)
{
	Bitboard bitboard;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Position position = {i, j};

			bitboard.setBit(position);

			ASSERT_TRUE(bitboard.getBit(position));

			bitboard.clearBit(position);

			ASSERT_FALSE(bitboard.getBit(position));
		}
	}
}

TEST_F(BitboardBitManipulationTest, allBitsSet)
{
	Bitboard bitboard;

	for (int index = 0; index < 64; index++)
	{
		Position position = {index / 8, index % 8};
		bitboard.setBit(position);
	}

	for (int index = 0; index < 64; index++)
	{
		ASSERT_TRUE(bitboard.getBit(index));
	}

	for (int index = 0; index < 64; index++)
	{
		Position position = {index / 8, index % 8};
		bitboard.clearBit(position);
	}

	for (int index = 0; index < 64; index++)
	{
		ASSERT_FALSE(bitboard.getBit(index));
	}
}

TEST_F(BitboardBitManipulationTest, noBitsSet)
{
	Bitboard bitboard;

	for (int index = 0; index < 64; index++)
	{
		ASSERT_FALSE(bitboard.getBit(index));
	}
}

TEST_F(BitboardBitManipulationTest, invalidPositions)
{
	Bitboard bitboard;

	std::vector<Position> invalidPositions = {
		{-1, 0},
		{0, -1},
		{-1, -1},
		{8, 0},
		{0, 8},
		{8, 8}};

	for (Position position : invalidPositions)
	{
		// Check that setBit throws an exception
		ASSERT_THROW(bitboard.setBit(position), std::invalid_argument);

		// Check that getBit throws an exception
		ASSERT_THROW(bitboard.getBit(position), std::invalid_argument);

		// Check that clearBit throws an exception
		ASSERT_THROW(bitboard.clearBit(position), std::invalid_argument);
	}
}
