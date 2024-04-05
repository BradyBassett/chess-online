#include <gtest/gtest.h>
#include <chrono>
#include "../../Chess/models/Game.h"

TEST(PerftTest, TestInitialPosition_Depth1)
{
	Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	// Perft(1) = 20
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(1), 20);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(1) took " << duration.count() << " milliseconds.\n";
}

TEST(PerftTest, TestInitialPosition_Depth2)
{
	Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	// Perft(2) = 400
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(2), 400);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(2) took " << duration.count() << " milliseconds.\n";
}