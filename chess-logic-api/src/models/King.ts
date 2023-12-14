import { PieceColor, PieceType } from "../Utilities/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class King extends Piece {
  private pieceType = PieceType.King;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    const moves = [
      { row: 1, col: 0 },   // Up
      { row: 1, col: 1 },   // Up-Right
      { row: 0, col: 1 },   // Right
      { row: -1, col: 1 },  // Down-Right
      { row: -1, col: 0 },  // Down
      { row: -1, col: -1 }, // Down-Left
      { row: 0, col: -1 },  // Left
      { row: 1, col: -1 },  // Up-Left
    ];
  
    // Check if the target square matches any of the possible moves
    for (const move of moves) {
      if (targetSquare.rowIndex === this.currentSquare.rowIndex + move.row &&
          targetSquare.colIndex === this.currentSquare.colIndex + move.col) {
        return true;
      }
    }

    return false;
  }
}
