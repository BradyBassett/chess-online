import React from "react";
import { render, screen, fireEvent } from "@testing-library/react";
import "@testing-library/jest-dom";
import Board from "./Board";


describe("Board", () => {
	it("renders the Board component correctly", () => {
		render(<Board />);
		const boardElement = screen.getByTestId("board");
		expect(boardElement).toBeInTheDocument();
	});

	it("handles square clicks and updates the board state", () => {
		render(<Board />);
		const squareElement1 = screen.getByTestId("square-a2");
		const squareElement2 = screen.getByTestId("square-a3");
		
		// initial state - pawn on a2, empty square on a3
		expect(squareElement1).not.toHaveClass("activeSquare");
		expect(squareElement2).not.toHaveClass("activeSquare");
		expect(squareElement1.firstChild).not.toBeNull();
		expect(squareElement2.firstChild).toBeNull();

		// click on square a2
		fireEvent.click(squareElement1);
		expect(squareElement1).toHaveClass("activeSquare");
		expect(squareElement2).not.toHaveClass("activeSquare");
		expect(squareElement1.firstChild).not.toBeNull();
		expect(squareElement2.firstChild).toBeNull();

		// click on square a3
		fireEvent.click(squareElement2);
		expect(squareElement1).not.toHaveClass("activeSquare");
		expect(squareElement2).not.toHaveClass("activeSquare");
		expect(squareElement1.firstChild).toBeNull();
		expect(squareElement2.firstChild).not.toBeNull();
	});
});
