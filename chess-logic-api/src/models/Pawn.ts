import { PieceColor, PieceType } from "../utils/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Pawn extends Piece {
  public pieceType = PieceType.Pawn;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    // if the pawn has already moved it can only move one square
    if (this.hasMoved) {
      return this.moveOneSquare(targetSquare, board);
    }
    // if the pawn hasn't moved it can move either one or two squares
    else {
      return this.moveOneSquare(targetSquare, board) || this.moveTwoSquares(targetSquare, board);
    }
  }

  private moveOneSquare(targetSquare: Square, board: Board): boolean {
    const moveDirection = this.color === PieceColor.Light ? 1 : -1

    if (targetSquare.rowIndex === this.currentSquare.rowIndex + moveDirection) {
      return true;
    }

    return false;
  }

  private moveTwoSquares(targetSquare: Square, board: Board): boolean {
    const moveDirection = this.color === PieceColor.Light ? 2 : -2

    if (targetSquare.rowIndex === this.currentSquare.rowIndex + moveDirection) {
      return true;
    }

    return false;
  }
}
