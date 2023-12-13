import Piece from "./Piece";


export default class Knight extends Piece {
  private pieceType = "knight";

  constructor(color: string) {
    super(color);
  }
}
