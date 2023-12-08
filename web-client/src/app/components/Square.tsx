import React, { useState } from "react";
import { PossiblePiece } from "../components/Board";

import styles from '../../styles/square.module.scss';


interface SquareProps {
  color: "light" | "dark";
  children: PossiblePiece;
  onClick: () => void;
}

export default function Square({color, children, onClick}: SquareProps): React.ReactElement {
  const [selected, setSelected] = useState(false);

  function handleClick() {
    onClick();
    setSelected(!selected);
  }

  return (
    <div 
      className={`${styles.square} ${color === "light" ? styles.light : styles.dark} ${selected ? styles.activeSquare : ""}`}
      onClick={handleClick}
    >
      {children}
    </div>
  );
}