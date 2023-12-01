"use client"

import React, { useState } from "react";
import styles from '../../styles/board.module.scss';
import Bishop from "./pieces/bishop";
import King from "./pieces/king";
import Knight from "./pieces/knight";
import Pawn from "./pieces/pawn";
import Queen from "./pieces/queen";
import Rook from "./pieces/rook";


import variables from "../../styles/_variables.module.scss";


interface Square {
  piece: string | null;
}

export default function Board(): React.ReactElement {
  const [board, setBoard] = useState(Array(8).fill(Array(8).fill(null)));
  const squareSize = parseFloat(variables.squareSize)

  return (
    <div className={styles.boardContainer}>
      <div className={styles.board}>
        {board.map((row, rowIndex) => (
          <div key={rowIndex} className={styles.boardRow}>
            {row.map((square: Square, colIndex: number) => (
              <div 
                key={colIndex} 
                className={`${styles.square} ${(rowIndex + colIndex) % 2 === 0 ? styles.light : styles.dark}`}>
                  {/* todo - insert pieces into position */}
                  <Queen size={squareSize} color="light"/>
              </div>
            ))}
          </div>
        ))}
      </div>
    </div>
  );
}
