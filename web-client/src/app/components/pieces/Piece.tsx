import React from "react";
import Image from "next/image";
import styles from "../../../styles/piece.module.scss";

interface PieceProps {
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
      className={styles.piece}
      /** TODO - Fix cursor not chaning to grab when hovering over piece */
      src={getIconSource()} 
      width={size}
      height={size}
      alt={type.charAt(0).toUpperCase() + type.slice(1)}
    />
  );
};
