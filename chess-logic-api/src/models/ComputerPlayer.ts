import Player from "./Player";
import { PlayerColor } from "../Utilities/enums";


export default class ComputerPlayer extends Player {
  constructor(color: PlayerColor) {
    super(color);
  }
}
