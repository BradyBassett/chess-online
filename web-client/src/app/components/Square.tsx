import React from "react";
import { PieceProps } from "./Piece";
import styles from "../../styles/square.module.scss";


export type PossiblePiece = React.ReactElement<PieceProps> | null;

export interface SquareProps {
  testid: string;
  color: "light" | "dark";
  children: PossiblePiece;
  isActive: boolean;
  isValidMove: boolean;
  isCapture: boolean;
  onClick: () => void;
}

export default function Square({testid, color, children, isActive, isValidMove, isCapture, onClick}: SquareProps): React.ReactElement {
  return (
    <div 
      data-testid={testid}
      className={`
          ${styles.square} 
          ${color === "light" ? styles.light : styles.dark} 
          ${isActive ? styles.activeSquare : ""}
        `}
      onClick={onClick}
    >
      <div className={styles.indicatorContainer}>
        {isValidMove && !children ? <div className={styles.validMoveIndicator} /> : null}
        {isCapture && children ? <div className={styles.captureIndicator} /> : null}
      </div>
      <div className={styles.pieceContainer}>
        {children}
      </div>
    </div>
  );
}
