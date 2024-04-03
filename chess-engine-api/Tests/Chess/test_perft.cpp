#include <gtest/gtest.h>
#include "../../Chess/models/Game.h"

TEST(PerftTest, TestInitialPosition)
{
	Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	ASSERT_EQ(game.Perft(1), 20);
	ASSERT_EQ(game.Perft(2), 400);
	// Add more depths as needed...
}
