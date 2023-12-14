import { PlayerColor } from "../Utilities/enums";


export default class Player {
  constructor(public color: PlayerColor) {
    this.color = color;
  }
}
