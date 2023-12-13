import Piece from "./Piece";


export default class Bishop extends Piece {
  private pieceType = "bishop";

  constructor(color: string) {
    super(color);
  }
}
