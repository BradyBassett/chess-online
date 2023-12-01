import React from "react";
import Piece from "./Piece";


interface KingProps {
  size: number;
  color: "dark" | "light";
}

export default function King({ size, color }: KingProps): React.ReactElement {
  return <Piece size={size} color={color} type="king" />;
}