import React from "react";
import { render, screen } from "@testing-library/react";
import "@testing-library/jest-dom";
import Piece, { PieceProps } from "../components/Piece";


describe("Piece component", () => {
	const pieces = ["bishop", "king", "knight", "pawn", "queen", "rook"];

	pieces.forEach((pieceType) => {
		it(`renders Piece component with dark ${pieceType} correctly`, () => {
			render(<Piece size={50} color="dark" type={pieceType as PieceProps["type"]} />);

			expect(screen.getByAltText(`Dark${pieceType.charAt(0).toUpperCase() + pieceType.slice(1)}`)).toBeInTheDocument();
			expect(screen.getByRole("img")).toHaveAttribute("src", `/images/Pieces/dark-${pieceType}.svg`);
		});

		it(`renders Piece component with light ${pieceType} correctly`, () => {
			render(<Piece size={50} color="light" type={pieceType as PieceProps["type"]} />);

			expect(screen.getByAltText(`Light${pieceType.charAt(0).toUpperCase() + pieceType.slice(1)}`)).toBeInTheDocument();
			expect(screen.getByRole("img")).toHaveAttribute("src", `/images/Pieces/light-${pieceType}.svg`);
		});
	});
});
