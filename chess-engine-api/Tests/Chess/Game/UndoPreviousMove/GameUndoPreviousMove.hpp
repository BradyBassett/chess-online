#ifndef GAMEUNDOPREVIOUSMOVE_HPP
#define GAMEUNDOPREVIOUSMOVE_HPP

#include "../GameTest.hpp"
#include "../../../../Chess/structs/Move.hpp"

struct GameUndoPreviousMoveParams
{
	std::string startingFen;
	std::vector<std::tuple<Position, Position, char>> moves; // from, to, promotion
	std::string expectedFen;
};

class GameUndoPreviousMove : public GameTest, public ::testing::TestWithParam<std::pair<std::string, GameUndoPreviousMoveParams>>
{
private:

protected:
	GameUndoPreviousMoveParams param;

public:
	GameUndoPreviousMove();
	static std::vector<std::pair<std::string, GameUndoPreviousMoveParams>> testCases;
};

#endif // GAMEUNDOPREVIOUSMOVE_HPP