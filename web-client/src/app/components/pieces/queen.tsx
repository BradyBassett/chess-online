import React from "react";
import Piece from "./piece";


interface QueenProps {
  size: number;
  color: "dark" | "light";
}

export default function Queen({ size, color }: QueenProps): React.ReactElement {
  return <Piece size={size} color={color} type="queen" />;
}