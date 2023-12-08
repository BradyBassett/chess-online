import React, { useEffect } from "react";
import Image from "next/image";

import styles from '../../styles/piece.module.scss';


export interface PieceProps {
  size: number;
  color: "dark" | "light";
  type: "bishop" | "king" | "knight" | "pawn" | "queen" | "rook";
}

export default function Piece({ size, color, type }: PieceProps): React.ReactElement {
  const getIconSource = () => {
    const imagePrefix = color === "dark" ? "dark-" : "light-";
    const imageSrc = `/images/Pieces/${imagePrefix}${type}.svg`;
    return imageSrc;
  };

  return (
    <Image 
      src={getIconSource()}
      width={size}
      height={size}
      alt={color.charAt(0).toUpperCase() + color.slice(1) + type.charAt(0).toUpperCase() + type.slice(1)} // takes first char in color and type and converts to uppercase
    />
  );
};
