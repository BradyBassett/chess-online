#include "Board.h"
#include <emscripten/bind.h>
#include "../utils/fenParser.h"

Board::Board(std::string fenPosition) {
	setStartingPosition(fenPosition);
}

void Board::setStartingPosition(std::string fenPosition) {
	squares.clear();

	std::vector<Square> parsedSquares = parseFenPosition(fenPosition);

	for (int i = 0; i < parsedSquares.size(); i += 8) {
		squares.push_back(std::vector<Square>(parsedSquares.begin() + i, parsedSquares.begin() + i + 8));
	}
}

Square Board::getSquare(int rowIndex, int colIndex) {
	return squares[rowIndex][colIndex];
}

emscripten::val Board::getSquareWrapper(int rowIndex, int colIndex) {
	Square square = getSquare(rowIndex, colIndex);

	emscripten::val result = emscripten::val::object();
	result.set("rowIndex", square.getRowIndex());
	result.set("colIndex", square.getColIndex());

	std::shared_ptr<Piece> piece = square.getPiece()

	if (piece != nullptr) {
		emscripten::val pieceObj = emscripten::val::object();
		pieceObj.set("hasMoved", piece->getHasMoved());
		pieceObj.set("isCaptured", piece->getIsCaptured());

		std::map<PieceColor, std::string> pieceColorMap = {
			{PieceColor::Light, "light"},
			{PieceColor::Dark, "dark"},
		}
		pieceObj.set("pieceColor", pieceColorMap[piece->getPieceColor()]);

		std::map<PieceType, std::string> pieceTypeMap = {
			{PieceType::Bishop, "bishop"};
			{PieceType::King, "king"};
			{PieceType::Knight, "knight"};
			{PieceType::Pawn, "pawn"};
			{PieceType::Queen, "queen"};
			{PieceType::Rook, "rook"};
		}
		pieceObj.set("pieceType", pieceTypeMap[piece->getPieceType()]);

		emscripten::val currentSquare = emscripten::val::object();
		currentSquare.set("rowIndex", square.getRowIndex());
		currentSquare.set("colIndex", square.getColIndex());

		pieceObj.set("currentSquare", currentSquare);
	}
	else {
		result.set("piece", emscripten::val::null());
	}

	return result;
}

EMSCRIPTEN_BINDINGS(board) {
	emscripten::class_<Board>("Board")
		.constructor<std::string>()
		.function("setStartingPosition", &Board::setStartingPosition)
		.function("getSquare", &Board::getSquareWrapper);
}
