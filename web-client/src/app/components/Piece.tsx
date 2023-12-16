import React from "react";
import Image from "next/image";
import styles from "../../styles/piece.module.scss";


export type PieceTypes = "bishop" | "king" | "knight" | "pawn" | "queen" | "rook";
export type PieceColors = "dark" | "light";

export interface PieceProps {
  size: number;
  color: PieceColors;
  type: "bishop" | "king" | "knight" | "pawn" | "queen" | "rook";
}

export default function Piece({ size, color, type }: PieceProps): React.ReactElement {
  function getIconSource() {
    const imagePrefix = color === "dark" ? "dark-" : "light-";
    const imageSrc = `/images/Pieces/${imagePrefix}${type}.svg`;
    return imageSrc;
  };

  if (Number.isNaN(size) || size === undefined || size === null || size === 0) {
    size = 45;
  }

  return (
    <Image 
      className={styles.piece}
      data-testid="piece"
      src={getIconSource()}
      width={size}
      height={size}
      alt={color.charAt(0).toUpperCase() + color.slice(1) + type.charAt(0).toUpperCase() + type.slice(1)} // takes first char in color and type and converts to uppercase
    />
  );
};
