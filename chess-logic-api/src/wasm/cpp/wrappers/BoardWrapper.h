#ifndef BOARDWRAPPER_H
#define BOARDWRAPPER_H

#include <emscripten/bind.h>
#include "../models/Board.h"

class BoardWrapper {
private:
  Board board;
public:
  BoardWrapper(std::string fenPosition);

  void setStartingPosition(std::string fenPosition);

	emscripten::val getSquare(int rowIndex, int colIndex);

};

#endif