#include <stdexcept>
#include <sstream>
#include "Game.hpp"
#include "../enums/PieceType.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Pawn.hpp"

Game::Game(std::string fenString)
{
	std::vector<std::string> fenParts = splitFenString(fenString);

	board = Board(fenParts[0], fenParts[2], fenParts[3]);

	parseActiveColor(fenParts[1]);
	parseHalfmoveClock(fenParts[4]);
	parseFullmoveNumber(fenParts[5]);

	// Add the starting position to the game state history
	gameStateHistory[getFen()] = 1;
}

std::vector<std::string> Game::splitFenString(const std::string &fenString)
{
	std::vector<std::string> parts;
	std::istringstream iss(fenString);
	std::string part;
	while (std::getline(iss, part, ' '))
	{
		parts.push_back(part);
	}

	return parts;
}

void Game::parseActiveColor(const std::string &color)
{
	activeColor = (color == "w") ? Color::White : Color::Black;
}

void Game::parseHalfmoveClock(const std::string &halfmove)
{
	halfMoveClock = std::stoi(halfmove);
}

void Game::parseFullmoveNumber(const std::string &fullmove)
{
	fullMoveNumber = std::stoi(fullmove);
}

Color Game::getActiveColor()
{
	return activeColor;
}

void Game::switchActiveColor()
{
	activeColor = (activeColor == Color::White) ? Color::Black : Color::White;
}

Board &Game::getBoard()
{
	return board;
}

std::string Game::ascii()
{
	std::string result;

	for (int i = 0; i < 8; i++)
	{
		result += "--+---+---+---+---+---+---+---+---+\n";
		result += std::to_string(8 - i) + " | ";
		for (int j = 0; j < 8; j++)
		{
			Square &square = board.getSquare(i, j);
			std::shared_ptr<Piece> piece = square.getPiece();
			result += pieceToAscii(piece);
			result += " | ";
		}
		result += "\n";
	}

	return result += "--+---+---+---+---+---+---+---+---+\n  | a | b | c | d | e | f | g | h |\n";
}

char Game::pieceToAscii(std::shared_ptr<Piece> piece)
{
	if (!piece)
	{
		return ' ';
	}

	Color pieceColor = piece->getPieceColor();

	switch (piece->getPieceType())
	{
	case PieceType::Pawn:
		return (pieceColor == Color::White) ? 'P' : 'p';
	case PieceType::Knight:
		return (pieceColor == Color::White) ? 'N' : 'n';
	case PieceType::Bishop:
		return (pieceColor == Color::White) ? 'B' : 'b';
	case PieceType::Rook:
		return (pieceColor == Color::White) ? 'R' : 'r';
	case PieceType::Queen:
		return (pieceColor == Color::White) ? 'Q' : 'q';
	case PieceType::King:
		return (pieceColor == Color::White) ? 'K' : 'k';
	default:
		return ' ';
	}
}

PieceType Game::charToPieceType(char piece)
{
	switch (piece)
	{
	case 'p':
		return PieceType::Pawn;
		break;
	case 'n':
		return PieceType::Knight;
		break;
	case 'b':
		return PieceType::Bishop;
		break;
	case 'r':
		return PieceType::Rook;
		break;
	case 'q':
		return PieceType::Queen;
		break;
	case 'k':
		return PieceType::King;
		break;
	default:
		throw std::invalid_argument("Invalid piece type");
	}
}

Move Game::composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece)
{
	Move move;
	move.color = activeColor;
	move.from = from;
	move.to = to;
	move.piece = board.getSquare(from).getPiece()->getPieceType();

	if (move.piece == PieceType::Pawn)
	{
		if (promotion != '\0')
		{
			move.setFlag(MoveFlag::Promotion);
			move.promotion = charToPieceType(promotion);
		}
		else if (abs(from.row - to.row) == 2)
		{
			move.setFlag(MoveFlag::PawnPush);
		}
	}

	if (promotion != '\0' && move.piece == PieceType::Pawn)
	{
		move.setFlag(MoveFlag::Promotion);
		move.promotion = charToPieceType(promotion);
	}

	if (capturedPiece.has_value() && capturedPiece.value()->getPieceColor() != activeColor)
	{
		if (move.piece == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !board.getSquare(to).getPiece())
		{
			move.setFlag(MoveFlag::EnPassant);
		}
		else
		{
			move.setFlag(MoveFlag::StandardCapture);
		}
		move.capturedPiece = capturedPiece.value()->getPieceType();
	}
	else
	{
		move.setFlag(MoveFlag::NonCapture);
	}

	if (move.piece == PieceType::King && to.col > from.col)
	{
		move.setFlag(MoveFlag::KingsideCastling);
	}
	else if (move.piece == PieceType::King && to.col < from.col)
	{
		move.setFlag(MoveFlag::QueensideCastling);
	}

	return move;
}

void Game::validateGenericMove(Position from, Position to, Piece &fromPiece, Square &toSquare)
{
	// check if it's the right turn
	if (fromPiece.getPieceColor() != activeColor)
	{
		throw std::invalid_argument("Invalid move - You can only move your own pieces");
	}

	// Check if target square is the same as the current square
	if (to == from)
	{
		throw std::invalid_argument("Invalid move - Piece must move to a different square");
	}

	// Check if target square contains a piece of the same color
	if (toSquare.getPiece() != nullptr && toSquare.getPiece()->getPieceColor() == fromPiece.getPieceColor())
	{
		throw std::invalid_argument("Invalid move - Piece cannot capture a piece of the same color");
	}

	// Check if the move is going through another piece
	if (!board.isPathClear(from, to, std::make_shared<Piece>(fromPiece)))
	{
		throw std::invalid_argument("Invalid move - Path is not clear");
	}
}

void Game::validatePawnMove(Position from, Position to, Piece &fromPiece, Square &toSquare, char promotion)
{
	if (fromPiece.getPieceType() == PieceType::Pawn)
	{
		Pawn &pawn = dynamic_cast<Pawn &>(fromPiece);

		// check if the pawn is moving diagonally
		if (abs(to.col - from.col) == 1 && abs(to.row - from.row) == 1)
		{
			if (toSquare.getPiece() == nullptr)
			{
				int enPassantEligibleRow = pawn.getPieceColor() == Color::White ? 3 : 4;
				if (from.row == enPassantEligibleRow)
				{
					Square *enPassantTargetSquare = board.getEnPassantTargetSquare();
					if (enPassantTargetSquare == nullptr || to != board.getEnPassantTargetSquare()->getPosition())
					{
						throw std::invalid_argument("Invalid move - Pawn can only capture en passant if the opponents move was a pawn move of 2 squares that landed next to this pawn");
					}
				}
				else
				{
					throw std::invalid_argument("Invalid move - Pawn cannot move diagonally unless it is capturing an opponent's piece");
				}
			}
		}
		// check if the pawn is moving orthogonally
		else
		{
			if (pawn.getHasMoved())
			{
				if (!pawn.canMoveOneSquare(to))
				{
					throw std::invalid_argument("Invalid move - Pawn can only move one square forward after its first move");
				}
			}
			else
			{
				if (!pawn.canMoveOneSquare(to) && !pawn.canMoveTwoSquares(to))
				{
					throw std::invalid_argument("Invalid move - Pawn can only move two squares forward if the square in front of it is empty and it is its first move");
				}
			}
		}

		// check if move is a promotion
		handlePawnPromotion(pawn, to, from, promotion);
	}
}

void Game::validateKingMove(Position from, Position to, Piece &fromPiece)
{
	// TODO - check for the following, moving into check, is in check, if in check can only move out of check or be protected
	if (fromPiece.getPieceType() == PieceType::King)
	{
		King &king = dynamic_cast<King &>(fromPiece);

		// If the target position is two squares away from the king then it is a castle
		if ((to.col == 2 && to.row == from.row) ||
			(to.col == 6 && to.row == from.row))
		{
			std::string errorMessage;

			if (!isValidCastle(from, to, king, errorMessage))
			{
				throw std::invalid_argument(errorMessage);
			}
		}
		// Otherwise, the king can only move one square in any direction
		else
		{
			if (abs(to.row - from.row) > 1 || abs(to.col - from.col) > 1)
			{
				throw std::invalid_argument("Invalid move - King can only move one square in any direction");
			}
		}
	}
}

void Game::validateMove(Position from, Position to, Piece &fromPiece, Square &toSquare, char promotion)
{
	// Generic move checks
	validateGenericMove(from, to, fromPiece, toSquare);
	// Pawn specific checks
	validatePawnMove(from, to, fromPiece, toSquare, promotion);
	// King specific checks
	validateKingMove(from, to, fromPiece);
}

Move Game::prepareMove(Position from, Position to, char promotion)
{
	Square &fromSquare = board.getSquare(from);
	Square &toSquare = board.getSquare(to);

	if (!fromSquare.getPiece())
	{
		throw std::invalid_argument("No piece at from position");
	}

	Piece &fromPiece = *fromSquare.getPiece();

	// Move validation
	validateMove(from, to, fromPiece, toSquare, promotion);

	// If the move is a capture, store the captured piece
	std::optional<std::shared_ptr<Piece>> capturedPiece = getCapturedPiece(toSquare, from, to, fromPiece);

	// if a piece was captured, decrement the piece count
	if (capturedPiece.has_value())
	{
		board.decrementPieceCount(capturedPiece.value()->getPieceColor(), capturedPiece.value()->getPieceType());
	}

	// compose the move struct
	Move move = composeMoveStruct(from, to, promotion, capturedPiece);

	if (getInCheck(getActiveColor()))
	{
		// TODO - EVENTUALLY USE THE UNDO MOVE FUNCTION INSTEAD OF SIMULATING THE MOVE
		Board tempBoard = board;
		tempBoard.setupMove(move);

		if (isInCheck(getActiveColor(), tempBoard.getKing(getActiveColor())->getCurrentPosition()))
		{
			throw std::invalid_argument("Invalid move - King is still in check");
		}
	}

	return move;
}

void Game::executeMove(Move move)
{
	Piece &fromPiece = *board.getSquare(move.from).getPiece();

	// add the move to the list of moves
	addMove(move);

	// update castling availability if the move was the first move of a rook or the king
	board.updateCastlingAvailability(fromPiece);

	// update en passant target square if the move was a double pawn push
	board.updateEnPassantTargetSquare(fromPiece, move.from, move.to);

	// increment half move clock if the move is not a pawn move or a capture
	if (fromPiece.getPieceType() != PieceType::Pawn && !move.capturedPiece.has_value())
	{
		incrementHalfMoveClock();
	}
	else
	{
		resetHalfMoveClock();
	}

	// move the piece
	board.setupMove(move);
}

void Game::postMoveChecks()
{
	// Determine the color of the other player
	Color otherColor = (getActiveColor() == Color::Black) ? Color::White : Color::Black;

	// Increment full move number if the move was made by black
	if (getActiveColor() == Color::Black)
	{
		incrementFullMoveNumber();
	}

	// Check if the move put the other king in check
	setInCheck(otherColor, isInCheck(otherColor, board.getKing(otherColor)->getCurrentPosition()));

	// Add the new position to the game state history, incrementing the count if it already exists
	gameStateHistory[getFen()]++;

	// Set full move number and half move clock on the move struct
	getLastMove().fullMoveNumber = getFullMoveNumber();
	getLastMove().halfMoveClock = getHalfMoveClock();

	// change turn
	switchActiveColor();
}

void Game::attemptMove(Position from, Position to, char promotion)
{
	Move move = prepareMove(from, to, promotion);
	executeMove(move);
	postMoveChecks();
}

void Game::handlePawnPromotion(Pawn &pawn, Position to, Position from, char promotion)
{
	Square &toSquare = board.getSquare(to);
	Bitboard &pawnBitboard = board.getBitboard(getActiveColor(), PieceType::Pawn);
	Bitboard *pieceBitboard;

	if (pawn.canPromote(to))
	{
		board.getSquare(from).setPiece(nullptr);
		pawnBitboard.clearBit(from);

		switch (promotion)
		{
		case 'q':
			toSquare.setPiece(std::make_shared<Queen>(getActiveColor(), to));
			pieceBitboard = &board.getBitboard(getActiveColor(), PieceType::Queen);
			pieceBitboard->setBit(to);
			board.incrementPieceCount(getActiveColor(), PieceType::Queen);
			break;
		case 'r':
			toSquare.setPiece(std::make_shared<Rook>(getActiveColor(), to));
			pieceBitboard = &board.getBitboard(getActiveColor(), PieceType::Rook);
			pieceBitboard->setBit(to);
			board.incrementPieceCount(getActiveColor(), PieceType::Rook);
			break;
		case 'b':
			toSquare.setPiece(std::make_shared<Bishop>(getActiveColor(), to));
			pieceBitboard = &board.getBitboard(getActiveColor(), PieceType::Bishop);
			pieceBitboard->setBit(to);
			board.incrementPieceCount(getActiveColor(), PieceType::Bishop);
			break;
		case 'n':
			toSquare.setPiece(std::make_shared<Knight>(getActiveColor(), to));
			pieceBitboard = &board.getBitboard(getActiveColor(), PieceType::Knight);
			pieceBitboard->setBit(to);
			board.incrementPieceCount(getActiveColor(), PieceType::Knight);
			break;
		default:
			throw std::invalid_argument("Invalid move - Promotion required");
		}
	}
}

std::optional<std::shared_ptr<Piece>> Game::getCapturedPiece(Square &toSquare, Position from, Position to, Piece &fromPiece)
{
	// regular capture
	if (toSquare.getPiece())
	{
		return toSquare.getPiece();
	}
	// en passant capture
	else if (fromPiece.getPieceType() == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !toSquare.getPiece())
	{
		return board.getSquare(to.row + (fromPiece.getPieceColor() == Color::White ? 1 : -1), to.col).getPiece();
	}
	// no capture
	else
	{
		return std::nullopt;
	}
}

std::vector<Move> Game::getMoves()
{
	return moves;
}

Move &Game::getLastMove()
{
	return moves.back();
}

void Game::addMove(Move move)
{
	moves.push_back(move);
}

void Game::undoPreviousMove()
{
	if (moves.empty())
	{
		throw std::invalid_argument("No moves found");
	}

	Move lastMove = moves.back();
	moves.pop_back();

	// if the move was a promotion, replace the promoted piece with a pawn
	if (lastMove.hasFlag(MoveFlag::Promotion))
	{
		// update the bitboard to remove the promoted piece and add a pawn
		board.getBitboard(lastMove.color, lastMove.promotion.value()).clearBit(lastMove.to);
		board.getBitboard(lastMove.color, PieceType::Pawn).setBit(lastMove.to);

		// create a pawn piece and place it on the board in the position of the promoted piece
		std::shared_ptr<Piece> pawn = std::make_shared<Piece>(lastMove.color, lastMove.to, PieceType::Pawn);
		board.getSquare(lastMove.to).setPiece(pawn);

		// decrement the piece count of the promoted piece and increment the piece count of the pawn
		board.decrementPieceCount(lastMove.color, lastMove.promotion.value());
		board.incrementPieceCount(lastMove.color, PieceType::Pawn);
	}

	// get the piece that was moved
	std::shared_ptr<Piece> piece = board.getSquare(lastMove.to).getPiece();
	Color color = piece->getPieceColor();

	// Restore piece to its original position
	board.getSquare(lastMove.from).setPiece(piece);
	board.getSquare(lastMove.to).setPiece(nullptr);
	piece->setCurrentPosition(lastMove.from);

	// Update the bitboard to show the piece in its original position
	board.getBitboard(color, piece->getPieceType()).clearBit(lastMove.to);
	board.getBitboard(color, piece->getPieceType()).setBit(lastMove.from);

	// if the move was a capture, restore the captured piece
	PieceType capturedPieceType = lastMove.capturedPiece.value();
	Color capturedPieceColor = color == Color::White ? Color::Black : Color::White;
	// Depending on the type of capture, place the captured piece back on the board
	if (lastMove.hasFlag(MoveFlag::StandardCapture))
	{
		std::shared_ptr<Piece> capturedPiece = std::make_shared<Piece>(capturedPieceColor, lastMove.to, capturedPieceType);
		board.getSquare(lastMove.to).setPiece(capturedPiece);

		// increment the piece count of the captured piece
		board.incrementPieceCount(capturedPieceColor, capturedPieceType);

		// update the bitboard to show the captured piece
		board.getBitboard(capturedPieceColor, capturedPieceType).setBit(lastMove.to);
	}
	else if (lastMove.hasFlag(MoveFlag::EnPassant))
	{
		Position capturePosition = {lastMove.to.row + (color == Color::White ? 1 : -1), lastMove.to.col};
		std::shared_ptr<Piece> capturedPiece = std::make_shared<Piece>(capturedPieceColor, capturePosition, capturedPieceType);
		board.getSquare(capturePosition).setPiece(capturedPiece);

		// increment the piece count of the captured piece
		board.incrementPieceCount(capturedPieceColor, capturedPieceType);

		// update the bitboard to show the captured piece
		board.getBitboard(capturedPieceColor, capturedPieceType).setBit(capturePosition);
	}

	// check if the move was a castle and restore the rook and reset any castling rights
	if (lastMove.hasFlag(MoveFlag::KingsideCastling))
	{
		board.getSquare(lastMove.to.row, 7).setPiece(board.getSquare(lastMove.to.row, 5).getPiece());
		board.getSquare(lastMove.to.row, 5).setPiece(nullptr);

		// update the bitboard to show the rook in its original position
		board.getBitboard(color, PieceType::Rook).clearBit({lastMove.to.row, 7});
		board.getBitboard(color, PieceType::Rook).setBit({lastMove.to.row, 5});

		// reset castling rights
		board.setCanCastleKingside(true, color);
		board.getKing(color)->setHasMoved(false);
		board.getRook(color, Side::KingSide)->setHasMoved(false);
	}
	else if (lastMove.hasFlag(MoveFlag::QueensideCastling))
	{
		board.getSquare(lastMove.to.row, 0).setPiece(board.getSquare(lastMove.to.row, 3).getPiece());
		board.getSquare(lastMove.to.row, 3).setPiece(nullptr);

		// update the bitboard to show the rook in its original position
		board.getBitboard(color, PieceType::Rook).clearBit({lastMove.to.row, 0});
		board.getBitboard(color, PieceType::Rook).setBit({lastMove.to.row, 3});

		// reset castling rights
		board.setCanCastleQueenside(true, color);
		board.getKing(color)->setHasMoved(false);
		board.getRook(color, Side::QueenSide)->setHasMoved(false);
	}

	// if the move was a double pawn push, update the en passant target square, and reset pawn has moved
	if (lastMove.hasFlag(MoveFlag::PawnPush))
	{
		// Check if the move prior to the last move was a pawn double push
		if (moves.back().hasFlag(MoveFlag::PawnPush))
		{
			// if it was, then the en passant target square should be the square that the pawn moved to
			board.setEnPassantTargetSquare(&board.getSquare((moves.back().from.row + moves.back().to.row) / 2, moves.back().from.col));
		}
		else
		{
			// if it wasn't, then the en passant target square should be null
			board.setEnPassantTargetSquare(nullptr);
		}

		// reset the has moved flag of the pawn
		piece->setHasMoved(false);
	}

	// Restore half move clock to its previous value if the move was a pawn move or a capture
	if (lastMove.hasFlag(MoveFlag::NonCapture) || lastMove.hasFlag(MoveFlag::PawnPush))
	{
		setHalfMoveClock(lastMove.halfMoveClock);
	}

	// Restore full move number to its previous value if the move was made by black
	if (lastMove.color == Color::Black)
	{
		setFullMoveNumber(lastMove.fullMoveNumber);
	}

	// if the last move put the other king in check, then the other king is no longer in check
	setInCheck(color, false);

	// switch the active color
	switchActiveColor();
}

uint8_t Game::getHalfMoveClock()
{
	return halfMoveClock;
}

uint8_t Game::getFullMoveNumber()
{
	return fullMoveNumber;
}

void Game::incrementHalfMoveClock()
{
	halfMoveClock++;
}

void Game::resetHalfMoveClock()
{
	halfMoveClock = 0;
}

void Game::incrementFullMoveNumber()
{
	fullMoveNumber++;
}

void Game::setHalfMoveClock(uint8_t value)
{
	halfMoveClock = value;
}

void Game::setFullMoveNumber(uint8_t value)
{
	fullMoveNumber = value;
}

bool Game::getInCheck(Color color)
{
	return color == Color::White ? whiteInCheck : blackInCheck;
}

void Game::setInCheck(Color color, bool value)
{
	if (color == Color::White)
	{
		whiteInCheck = value;
	}
	else
	{
		blackInCheck = value;
	}
}

bool Game::isInCheck(Color color, Position position)
{
	Bitboard opposingPieces = color == Color::White ? board.getBlackPiecesBitboard() : board.getWhitePiecesBitboard();

	for (int square = 0; square < 64; square++)
	{
		if (opposingPieces.getBit(square))
		{
			std::shared_ptr<Piece> piece = board.getSquare(square).getPiece();
			Bitboard attackTable = board.getAttackTable(piece->getPieceColor(), piece->getPieceType())[square];
			if (attackTable.getBit(position))
			{
				return true;
			}
		}
	}

	return false;
}

bool Game::isCheckmate(Color color)
{
	// get the king
	std::shared_ptr<King> king = board.getKing(color);
	// get the potential moves of the king
	Bitboard kingMoves = king->getPotentialMoves();

	// for each set bit in the bitboard, simulate the move and check if the king is still in check
	for (int square = 0; square < 64; square++)
	{
		if (kingMoves.getBit(square))
		{
			Position to = {square / 8, square % 8};
			Move move = composeMoveStruct(king->getCurrentPosition(), to, '\0', std::nullopt);
			Board tempBoard = board;
			tempBoard.setupMove(move);
			if (!isInCheck(color, to))
			{
				// If there is any move that the king can make that would not result in check, return false
				return false;
			}
		}
	}

	// If no such move is found, check if any other piece of the same color can block the check
	// First loop through all the squares and when a piece is found, get the potential moves of that piece
	for (int square = 0; square < 64; square++)
	{
		if (board.getAllPiecesBitboard().getBit(square))
		{
			std::shared_ptr<Piece> piece = board.getSquare(square).getPiece();
			Bitboard pieceMoves = piece->getPotentialMoves();

			// For each set bit in the bitboard, simulate the move and check if the king is still in check
			for (int i = 0; i < 64; i++)
			{
				if (pieceMoves.getBit(i))
				{
					Position from = piece->getCurrentPosition();
					Position to = {i / 8, i % 8};
					Move move = composeMoveStruct(from, to, '\0', std::nullopt);
					Board tempBoard = board;
					tempBoard.setupMove(move);
					if (!isInCheck(color, king->getCurrentPosition()))
					{
						// If there is any move that the piece can make that would not result in check, return false
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool Game::isStalemate(Color color)
{
	// check if the king is in check
	if ((color == Color::White && whiteInCheck) || (color == Color::Black && blackInCheck))
	{
		return false;
	}

	// check if the the current player has any legal moves
	Bitboard playerPieces = color == Color::White ? board.getWhitePiecesBitboard() : board.getBlackPiecesBitboard();

	for (int square = 0; square < 64; square++)
	{
		// If the square contains a piece of the current player then get the potential moves of that piece
		if (playerPieces.getBit(square))
		{
			std::shared_ptr<Piece> piece = board.getSquare(square).getPiece();
			Bitboard pieceMoves = piece->getPotentialMoves();

			for (int i = 0; i < 64; i++)
			{
				// For each set bit in the bitboard, check if the move is valid
				if (pieceMoves.getBit(i))
				{
					Position from = piece->getCurrentPosition();
					Position to = {i / 8, i % 8};

					// If the move is valid then the player is not in stalemate
					try
					{
						validateMove(from, to, *piece, board.getSquare(to), '\0');
						return false;
					}
					// If the move is invalid then continue to the next move
					catch (const std::exception &e)
					{
						continue;
					}
				}
			}
		}
	}

	return true;
}

bool Game::isFiftyMoveRule()
{
	if (halfMoveClock >= 100)
	{
		return true;
	}

	return false;
}

bool Game::isThreefoldRepetition()
{
	if (gameStateHistory[getFen()] >= 3)
	{
		return true;
	}

	return false;
}

bool Game::isInsufficientMaterial()
{
	// Check for insufficient material conditions.
	if (board.getPieceCount(Color::White, PieceType::King) == 1 && board.getPieceCount(Color::Black, PieceType::King) == 1)
	{
		// Only kings left.
		if (board.getPieceCount(Color::White, PieceType::Pawn) == 0 && board.getPieceCount(Color::Black, PieceType::Pawn) == 0 &&
			board.getPieceCount(Color::White, PieceType::Rook) == 0 && board.getPieceCount(Color::Black, PieceType::Rook) == 0 &&
			board.getPieceCount(Color::White, PieceType::Queen) == 0 && board.getPieceCount(Color::Black, PieceType::Queen) == 0)
		{
			// Only kings and possibly bishops or knights left.
			if (board.getPieceCount(Color::White, PieceType::Bishop) <= 1 && board.getPieceCount(Color::Black, PieceType::Bishop) <= 1 &&
				board.getPieceCount(Color::White, PieceType::Knight) <= 1 && board.getPieceCount(Color::Black, PieceType::Knight) <= 1)
			{
				return true;
			}
		}
	}

	// There is sufficient material for a checkmate.
	return false;
}

bool Game::isResignation()
{
	// TODO - Implement resignation detection
	return true;
}

bool Game::isTimeout()
{
	// TODO - Implement timeout detection
	return true;
}

GameEndState Game::isGameOver()
{
	if (isCheckmate(Color::White) || isCheckmate(Color::Black))
	{
		return GameEndState::CHECKMATE;
	}
	else if (isStalemate(Color::White) || isStalemate(Color::Black))
	{
		return GameEndState::STALEMATE;
	}
	else if (isResignation())
	{
		return GameEndState::RESIGNATION;
	}
	else if (isTimeout())
	{
		return GameEndState::TIMEOUT;
	}
	else if (isThreefoldRepetition())
	{
		return GameEndState::THREEFOLD_REPETITION;
	}
	else if (isInsufficientMaterial())
	{
		return GameEndState::INSUFFICIENT_MATERIAL;
	}
	else if (isFiftyMoveRule())
	{
		return GameEndState::FIFTY_MOVE_RULE;
	}
	// TODO - Implement all other game end states
	return GameEndState::IN_PROGRESS;
}

bool Game::isValidCastle(Position from, Position to, King &king, std::string &errorMessage)
{
	if (!(board.getCanCastleKingside(king.getPieceColor()) || board.getCanCastleQueenside(king.getPieceColor())))
	{
		errorMessage = "Invalid move - No castling rights";
		return false;
	}

	// If king is trying to castle queen side get the rook on the queen side and vice versa
	Side side = to.col == 2 ? Side::QueenSide : Side::KingSide;
	std::shared_ptr<Rook> rook = board.getRook(king.getPieceColor(), side);

	if (king.getHasMoved())
	{
		errorMessage = "Invalid move - King has already moved";
		return false;
	}
	else if (rook->getHasMoved())
	{
		std::string rookSide = side == Side::QueenSide ? "Queenside " : "Kingside ";
		errorMessage = "Invalid move - " + rookSide + "Rook has already moved";
		return false;
	}
	else if (king.getIsInCheck())
	{
		errorMessage = "Invalid move - King is in check";
		return false;
	}

	int direction = side == Side::QueenSide ? -1 : 1;
	for (int i = from.col + direction; i != rook->getCurrentPosition().col; i + direction)
	{
		Square &square = board.getSquare(from.row, i);
		// If there is a piece between the king and the rook then the king cannot castle
		if (square.getPiece() != nullptr)
		{
			errorMessage = "Invalid move - King cannot castle through other pieces";
			return false;
		}

		if (isInCheck(king.getPieceColor(), {from.row, i}))
		{
			errorMessage = "Invalid move - King cannot castle through check";
			return false;
		}
	}

	return true;
}

std::string Game::getFen()
{
	std::string fen = "";
	int emptySquares = 0;

	// Piece placement
	for (int i = 0; i < board.getSquares().size(); i++)
	{
		std::vector<Square> row = board.getSquares()[i];
		emptySquares = 0;

		for (Square square : row)
		{
			if (square.getPiece() != nullptr)
			{
				if (emptySquares > 0)
				{
					fen += std::to_string(emptySquares);
					emptySquares = 0;
				}

				fen += pieceToAscii(square.getPiece());
			}
			else
			{
				emptySquares++;
			}
		}

		if (emptySquares > 0)
		{
			fen += std::to_string(emptySquares);
		}

		if (i < board.getSquares().size() - 1)
		{
			fen += "/";
		}
	}

	// Active color
	fen += " " + std::string(activeColor == Color::White ? "w" : "b");

	// Castling availability
	std::string castling = "";
	castling += (board.getCanCastleKingside(Color::White) ? std::string("K") : std::string(""));
	castling += (board.getCanCastleQueenside(Color::White) ? std::string("Q") : std::string(""));
	castling += (board.getCanCastleKingside(Color::Black) ? std::string("k") : std::string(""));
	castling += (board.getCanCastleQueenside(Color::Black) ? std::string("q") : std::string(""));
	fen += " " + (castling.empty() ? "-" : castling);

	// En passant target square
	Square *enPassantTargetSquare = board.getEnPassantTargetSquare();
	if (enPassantTargetSquare != nullptr)
	{
		fen += " " + board.convertPositionToString(enPassantTargetSquare->getPosition());
	}
	else
	{
		fen += " -";
	}

	// Halfmove clock
	fen += " " + std::to_string(halfMoveClock);

	// Fullmove number
	fen += " " + std::to_string(fullMoveNumber);

	return fen;
}

std::vector<Move> Game::generateLegalMoves()
{
	std::vector<Move> legalMoves;

	// Loop through all the squares on the board
	for (int i = 0; i < 64; i++)
	{
		Square &square = board.getSquare(i);

		// If the square is empty or the piece is not the active color then continue
		if (!square.getPiece() || square.getPiece()->getPieceColor() != activeColor)
		{
			continue;
		}

		// Get the potential moves of the piece
		Bitboard potentialMoves = square.getPiece()->getPotentialMoves();

		// convert the bitboard into a vector of moves
		for (int j = 0; j < 64; j++)
		{
			if (potentialMoves.getBit(j))
			{
				Position from = square.getPosition();
				Position to = {j / 8, j % 8};
				Move move = composeMoveStruct(from, to, '\0', std::nullopt);

				// If the move is valid then add it to the list of legal moves
				try
				{
					validateMove(from, to, *square.getPiece(), board.getSquare(to), '\0');
					legalMoves.push_back(move);
				}
				// If the move is invalid then continue to the next move
				catch (const std::exception &e)
				{
					continue;
				}
			}
		}
	}

	return legalMoves;
}

uint64_t Game::Perft(int depth)
{
	if (depth == 0)
	{
		return 1;
	}

	uint64_t nodes = 0;
	std::vector<Move> moves = generateLegalMoves();
	for (Move move : moves)
	{
		executeMove(move);
		nodes += Perft(depth - 1);
		undoPreviousMove();
	}

	return nodes;
}