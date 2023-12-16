import { PlayerColor } from "../utils/enums";


export default abstract class Player {
  constructor(public color: PlayerColor) {
    this.color = color;
  }
}
