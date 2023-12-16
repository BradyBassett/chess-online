import { PieceColor, PieceType } from "../utils/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Rook extends Piece {
  public pieceType = PieceType.Rook;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    // if the target square is not in the same row or column as the current square, return false
    if (!super.targetSquareIsStraight(targetSquare)) {
      return false;
    }

    // if there are pieces between the valid path between the current square and the target square, return false
    return super.isValidStraightMove(targetSquare, board);
  }
}


// TODO - add logic for castling