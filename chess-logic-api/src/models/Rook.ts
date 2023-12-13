import Piece from "./Piece";


export default class Rook extends Piece {
  private pieceType = "rook";

  constructor(color: string) {
    super(color);
  }
}
