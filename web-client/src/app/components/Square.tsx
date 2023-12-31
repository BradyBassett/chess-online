import React from "react";
import { PieceProps } from "./Piece";
import styles from "../../styles/square.module.scss";


export type PossiblePiece = React.ReactElement<PieceProps> | null;

export interface SquareProps {
  testid: string;
  color: "light" | "dark";
  children: PossiblePiece;
  isActive: boolean;
  onClick: () => void;
}

export default function Square({testid, color, children, isActive, onClick}: SquareProps): React.ReactElement {
  return (
    <div 
      data-testid={testid}
      className={`${styles.square} ${color === "light" ? styles.light : styles.dark} ${isActive ? styles.activeSquare : ""}`}
      onClick={onClick}
    >
      {children}
    </div>
  );
}