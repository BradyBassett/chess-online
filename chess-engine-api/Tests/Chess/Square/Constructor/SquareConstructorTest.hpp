#ifndef SQUARECONSTRUCTORTEST_HPP
#define SQUARECONSTRUCTORTEST_HPP

#include "../SquareTest.hpp"

struct SquareConstructorTestParam
{
	Position position;
	std::shared_ptr<Piece> piece;
};

class SquareConstructorTest : public SquareTest, public ::testing::TestWithParam<std::pair<std::string, SquareConstructorTestParam>>
{
private:

protected:
	SquareConstructorTestParam param;

public:
	SquareConstructorTest();
	static std::vector<std::pair<std::string, SquareConstructorTestParam>> testCases;
};

#endif // SQUARECONSTRUCTORTEST_HPP