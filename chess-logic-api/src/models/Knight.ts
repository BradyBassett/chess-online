import { PieceColor, PieceType } from "../utils/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Knight extends Piece {
  public pieceType = PieceType.Knight;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    const moves = [
    { row: 2, col: 1 }, // up 2 right 1
    { row: 2, col: -1 }, // up 2 left 1
    { row: -2, col: 1 }, // down 2 right 1
    { row: -2, col: -1 }, // down 2 left 1
    { row: 1, col: 2 }, // up 1 right 2
    { row: 1, col: -2 }, // up 1 left 2
    { row: -1, col: 2 }, // down 1 right 2
    { row: -1, col: -2 }, // down 1 left 2
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
