import React, { useState } from "react";
import { PossiblePiece } from "../components/Board";

import styles from '../../styles/square.module.scss';


interface SquareProps {
  color: "light" | "dark";
  children: PossiblePiece;
  isActive: boolean;
  onClick: () => void;
}

export default function Square({color, children, isActive, onClick}: SquareProps): React.ReactElement {
  return (
    <div 
      className={`${styles.square} ${color === "light" ? styles.light : styles.dark} ${isActive ? styles.activeSquare : ""}`}
      onClick={onClick}
    >
      {children}
    </div>
  );
}