import React from "react";
import Image from "next/image";
import styles from "../../styles/piece.module.scss";
import { PieceSymbol, Color } from "chess.js";


export interface PieceProps {
  size: number;
  color: Color;
  type: PieceSymbol;
}

export default function Piece({ size, color, type }: PieceProps): React.ReactElement {
  if (Number.isNaN(size) || size === undefined || size === null || size === 0) {
    size = 45;
  }

  const colorMap = {
    "b": "Black",
    "w": "White"
  };

  const typeMap = {
    "b": "Bishop",
    "k": "King",
    "n": "Knight",
    "p": "Pawn",
    "q": "Queen",
    "r": "Rook"
  };

  return (
    <Image 
      className={styles.piece}
      data-testid="piece"
      src={`/images/Pieces/${color}-${type}.svg`}
      width={size}
      height={size}
      alt={`${colorMap[color]} ${typeMap[type]}`}
    />
  );
};
