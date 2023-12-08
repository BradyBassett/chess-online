import React from "react";
import { PossiblePiece } from "../components/Board";

import styles from '../../styles/square.module.scss';


interface SquareProps {
  color: "light" | "dark";
  children: PossiblePiece
}

export default function Square({color, children}: SquareProps): React.ReactElement {
  return (
    <div className={`${styles.square} ${color === "light" ? styles.light : styles.dark}`}>
      {children}
    </div>
  );
}