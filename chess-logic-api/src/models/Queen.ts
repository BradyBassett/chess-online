import Piece from "./Piece";


export default class Queen extends Piece {
  private pieceType = "queen";

  constructor(color: string) {
    super(color);
  }
}
