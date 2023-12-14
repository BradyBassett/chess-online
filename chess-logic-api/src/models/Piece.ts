import { PieceColor } from "../Utilities/enums";
import Board from "./Board";

import Square from "./Square";


export default abstract class Piece {
  protected hasMoved: boolean = false;
  protected isCaptured: boolean = false;

  constructor(public color: PieceColor, public currentSquare: Square) {
    this.color = color;
    this.currentSquare = currentSquare;
  }

  protected isValidMove(targetSquare: Square, board: Board): boolean {
    // if target square is the same as current square, return false
    if (this.currentSquare === targetSquare) {
      return false;
    }

    // if the target square is occupied by a piece of the same color, return false
    if (targetSquare.piece && targetSquare.piece.color === this.color) {
      return false;
    }
    
    return true;
  }
}
