import React from "react";
import Piece from "./piece";


interface RookProps {
  size: number;
  color: "dark" | "light";
}

export default function Rook({ size, color }: RookProps): React.ReactElement {
  return <Piece size={size} color={color} type="rook" />;
}