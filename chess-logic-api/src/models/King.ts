import Piece from "./Piece";


export default class King extends Piece {
  private pieceType = "king";

  constructor(color: string) {
    super(color);
  }
}
