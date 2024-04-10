#include <gtest/gtest.h> // TODO - Remove this include once the file is reworked
#include <chrono>
#include "../../../Chess/models/Game.hpp"

class GameInitialPositionTest : public ::testing::Test
{
public:
	Game game;

	GameInitialPositionTest() : game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"){};
};

class PerftInitialPositionTest : public GameInitialPositionTest
{
};

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth1)
{
	// Perft(1) = 20
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(1), 20);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(1) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth2)
{
	// Perft(2) = 400
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(2), 400);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(2) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth3)
{
	// Perft(3) = 8902
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(3), 8902);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(3) took " << duration.count() << " milliseconds.\n";
}

// Continue with the same pattern for depths 4 to 9

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth4)
{
	// Perft(4) = 197281
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(4), 197281);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(4) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth5)
{
	// Perft(5) = 4865609
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(5), 4865609);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(5) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth6)
{
	// Perft(6) = 119060324
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(6), 119060324);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(6) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth7)
{
	// Perft(7) = 3195901860
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(7), 3195901860);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(7) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth8)
{
	// Perft(8) = 84998978956
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(8), 84998978956);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(8) took " << duration.count() << " milliseconds.\n";
}

TEST_F(PerftInitialPositionTest, TestInitialPosition_Depth9)
{
	// Perft(9) = 2439530234167
	auto start = std::chrono::high_resolution_clock::now();
	ASSERT_EQ(game.Perft(9), 2439530234167);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Perft(9) took " << duration.count() << " milliseconds.\n";
}