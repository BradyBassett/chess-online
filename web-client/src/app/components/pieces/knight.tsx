import React from "react";
import Piece from "./Piece";


interface KnightProps {
  size: number;
  color: "dark" | "light";
}

export default function Knight({ size, color }: KnightProps): React.ReactElement {
  return <Piece size={size} color={color} type="knight" />;
}