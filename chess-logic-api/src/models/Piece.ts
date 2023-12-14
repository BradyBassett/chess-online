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

  public abstract isValidMove(targetSquare: Square, board: Board): boolean;
}
