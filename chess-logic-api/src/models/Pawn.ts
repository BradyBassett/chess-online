import Piece from "./Piece";


export default class Pawn extends Piece {
  private pieceType = "pawn";

  constructor(color: string) {
    super(color);
  }
}
