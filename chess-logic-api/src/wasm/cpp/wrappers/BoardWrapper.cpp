#include "BoardWrapper.h"

BoardWrapper::BoardWrapper(std::string fenPosition) : board(fenPosition) {}

void BoardWrapper::setStartingPosition(std::string fenPosition) {
  board.setStartingPosition(fenPosition);
}

emscripten::val BoardWrapper::getSquare(int rowIndex, int colIndex) {
	Square square = board.getSquare(rowIndex, colIndex);

	emscripten::val result = emscripten::val::object();
	result.set("rowIndex", square.getRowIndex());
	result.set("colIndex", square.getColIndex());

	std::shared_ptr<Piece> piece = square.getPiece();

	if (piece != nullptr) {
		emscripten::val pieceObj = emscripten::val::object();
		pieceObj.set("hasMoved", piece->getHasMoved());
		pieceObj.set("isCaptured", piece->getIsCaptured());

		std::map<PieceColor, std::string> pieceColorMap = {
			{PieceColor::Light, "light"},
			{PieceColor::Dark, "dark"},
		};
		pieceObj.set("pieceColor", pieceColorMap[piece->getPieceColor()]);

		std::map<PieceType, std::string> pieceTypeMap = {
			{PieceType::Bishop, "bishop"},
			{PieceType::King, "king"},
			{PieceType::Knight, "knight"},
			{PieceType::Pawn, "pawn"},
			{PieceType::Queen, "queen"},
			{PieceType::Rook, "rook"}
		};

		pieceObj.set("pieceType", pieceTypeMap[piece->getPieceType()]);

		emscripten::val currentSquare = emscripten::val::object();
		currentSquare.set("rowIndex", square.getRowIndex());
		currentSquare.set("colIndex", square.getColIndex());

		pieceObj.set("currentSquare", currentSquare);
    result.set("piece", pieceObj);
	}
	else {
		result.set("piece", emscripten::val::null());
	}

	return result;
}

EMSCRIPTEN_BINDINGS(board) {
	emscripten::class_<BoardWrapper>("Board")
		.constructor<std::string>()
		.function("setStartingPosition", &BoardWrapper::setStartingPosition)
		.function("getSquare", &BoardWrapper::getSquare);
}
