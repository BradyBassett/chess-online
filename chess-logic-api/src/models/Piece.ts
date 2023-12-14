import { PieceColor } from "../Utilities/enums";


export default class Piece {
  protected hasMoved: boolean = false;
  protected isCaptured: boolean = false;

  constructor(public color: PieceColor) {
    this.color = color;
  }

  public move() {
    if (!this.hasMoved) this.hasMoved = true;
  }

  public capture() {
    this.isCaptured = true;
  }
}
