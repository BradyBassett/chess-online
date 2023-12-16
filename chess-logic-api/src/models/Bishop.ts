import { PieceColor, PieceType } from "../utils/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Bishop extends Piece {
  public pieceType = PieceType.Bishop;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    // if the targetSquare is not a diagonal of currentSquare, return false
    if (!super.targetSquareIsDiagonal(targetSquare)) {
      return false;
    }

    // if there are pieces between the valid path between the current square and the target square, return false
    return super.isValidDiagonalMove(targetSquare, board);
  }
}
