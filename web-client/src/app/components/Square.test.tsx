import React from "react";
import { render, screen, fireEvent } from "@testing-library/react";
import "@testing-library/jest-dom";
import Square from "./Square";
import Piece from "../components/Piece";


describe("Square component with light color and null child", () => {
	it("renders Square component light color and null child", () => {
		render(<Square testid="square" color="light" isActive={false} onClick={() => {}}>{null}</Square>);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("light");
	});

	it("renders Square component with dark color and null child", () => {
		render(<Square testid="square" color="dark" isActive={false} onClick={() => {}}>{null}</Square>);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("dark");
	});

	it("renders Square component with light and activeSquare classes and a null child", () => {
		render(<Square testid="square" color="light" isActive={true} onClick={() => {}}>{null}</Square>);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("activeSquare");
		expect(screen.getByTestId("square")).toHaveClass("light");
	});

	it("renders Square component with dark and activeSquare classes and a null child", () => {
		render(<Square testid="square" color="dark" isActive={true} onClick={() => {}}>{null}</Square>);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("activeSquare");
		expect(screen.getByTestId("square")).toHaveClass("dark");
	});

	it("renders Square component light color and Piece child", () => {
		render(
			<Square testid="square" color="light" isActive={false} onClick={() => {}}>
				<Piece size={50} color="dark" type="queen" />
			</Square>
		);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("piece")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("light");
	});

	it("renders Square component with dark color and Piece child", () => {
		render(
			<Square testid="square" color="dark" isActive={false} onClick={() => {}}>
				<Piece size={50} color="light" type="king" />
			</Square>
		);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("piece")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("dark");
	});

	it("renders Square component with light and activeSquare classes and a Piece child", () => {
		render(
			<Square testid="square" color="light" isActive={true} onClick={() => {}}>
				<Piece size={50} color="light" type="pawn" />
			</Square>
		);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("piece")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("activeSquare");
		expect(screen.getByTestId("square")).toHaveClass("light");
	});

	it("renders Square component with dark and activeSquare classes and a Piece child", () => {
		render(
			<Square testid="square" color="dark" isActive={true} onClick={() => {}}>
				<Piece size={50} color="dark" type="rook" />
			</Square>
		);

		expect(screen.getByTestId("square")).toBeInTheDocument();
		expect(screen.getByTestId("piece")).toBeInTheDocument();
		expect(screen.getByTestId("square")).toHaveClass("activeSquare");
		expect(screen.getByTestId("square")).toHaveClass("dark");
	});
	
	it("invokes onClick callback when square is clicked", () => {
		const onClickMock = jest.fn();
		render(<Square testid="square" color="light" isActive={false} onClick={onClickMock}>{null}</Square>);

		fireEvent.click(screen.getByTestId("square"));

		expect(onClickMock).toHaveBeenCalled();
	});
});
