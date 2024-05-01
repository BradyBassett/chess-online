#ifndef GAMEATTEMPTMOVETEST_HPP
#define GAMEATTEMPTMOVETEST_HPP

#include "../GameTest.hpp"

struct GameAttemptMoveTestParam
{
	std::string fen;
	Position from;
	Position to;
	char promotion;
};

class GameAttemptMoveTest : public GameTest, public ::testing::TestWithParam<std::pair<std::string, GameAttemptMoveTestParam>>
{
private:

protected:
	GameAttemptMoveTestParam param;

public:
	GameAttemptMoveTest();
	static std::vector<std::pair<std::string, GameAttemptMoveTestParam>> testCases;
};

#endif // GAMEATTEMPTMOVETEST_HPP