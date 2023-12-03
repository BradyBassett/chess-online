import React from "react";
import Image from "next/image";
import styles from "../../styles/piece.module.scss";
import PieceProps from "@/interfaces/PieceProps";


export default function Piece({ size, color, type }: PieceProps): React.ReactElement {
  const getIconSource = () => {
    const imagePrefix = color === "dark" ? "dark-" : "light-";
    const imageSrc = `/images/Pieces/${imagePrefix}${type}.svg`;
    return imageSrc;
  };

  return (
    <Image 
      className={styles.piece}
      src={getIconSource()} 
      width={size}
      height={size}
      alt={color.charAt(0).toUpperCase() + color.slice(1) + type.charAt(0).toUpperCase() + type.slice(1)} // takes first char in color and type and converts to uppercase
    />
  );
};
