// FIXME - eventually move these tests and refactor to fit in chess-logic-api


import { parseFenPosition, isDigitFrom1To8 } from "./fenParser";


describe("parseFenPosition function", () => {
	it("should return an array of React elements representing chess pieces in the starting position", () => {
		const fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
		const pieces = parseFenPosition(fenPosition);

		// Chessboard has 64 squares
		expect(pieces).toHaveLength(64);

		// Check for the presence of React elements with the correct type and color props or null values in the expected positions
		const expectedElements = [
			["rook", "dark"], ["knight", "dark"], ["bishop", "dark"], ["queen", "dark"], ["king", "dark"], ["bishop", "dark"], ["knight", "dark"], ["rook", "dark"],
			["pawn", "dark"], ["pawn", "dark"], ["pawn", "dark"], ["pawn", "dark"], ["pawn", "dark"], ["pawn", "dark"], ["pawn", "dark"], ["pawn", "dark"],
			null, null, null, null, null, null, null, null,
			null, null, null, null, null, null, null, null,
			null, null, null, null, null, null, null, null,
			null, null, null, null, null, null, null, null,
			["pawn", "light"], ["pawn", "light"], ["pawn", "light"], ["pawn", "light"], ["pawn", "light"], ["pawn", "light"], ["pawn", "light"], ["pawn", "light"],
			["rook", "light"], ["knight", "light"], ["bishop", "light"], ["queen", "light"], ["king", "light"], ["bishop", "light"], ["knight", "light"], ["rook", "light"],
		];

		expectedElements.forEach((expectedElement, index) => {
			if (expectedElement === null) {
				expect(pieces[index]).toBeNull();
			} else {
				expect(pieces[index]).toBeInstanceOf(Object);

				const [expectedType, expectedColor] = expectedElement;
				const actualType = pieces[index]!.props.type;
				const actualColor = pieces[index]!.props.color;

				expect(actualType).toBe(expectedType);
				expect(actualColor).toBe(expectedColor);
			}
		});
	});

	it("should return an array of React elements representing chess pieces in a random position", () => {
		const fenPosition = "r1bk3r/p2pBpNp/n4n2/1p1NP2P/6P1/3P4/P1P1K3/q5b1";
		const pieces = parseFenPosition(fenPosition);
	
		// Chessboard has 64 squares
		expect(pieces).toHaveLength(64);
	
		// Check for the presence of React elements with the correct type and color props or null values in the expected positions
		const expectedElements = [
			["rook", "dark"], null, ["bishop", "dark"], ["king", "dark"], null, null, null, ["rook", "dark"],
			["pawn", "dark"], null, null, ["pawn", "dark"], ["bishop", "light"], ["pawn", "dark"], ["knight", "light"], ["pawn", "dark"],
			["knight", "dark"], null, null, null, null, ["knight", "dark"], null, null,
			null, ["pawn", "dark"], null, ["knight", "light"], ["pawn", "light"], null, null, ["pawn", "light"],
			null, null, null, null, null, null, ["pawn", "light"], null,
			null, null, null, ["pawn", "light"], null, null, null, null,
			["pawn", "light"], null, ["pawn", "light"], null, ["king", "light"], null, null, null,
			["queen", "dark"], null, null, null, null, null, ["bishop", "dark"], null,
		];

		expectedElements.forEach((expectedElement, index) => {
			if (expectedElement === null) {
				expect(pieces[index]).toBeNull();
			} else {
				expect(pieces[index]).toBeInstanceOf(Object);
				
				const [expectedType, expectedColor] = expectedElement;
				const actualType = pieces[index]!.props.type;
				const actualColor = pieces[index]!.props.color;
				
				expect(actualType).toBe(expectedType);
				expect(actualColor).toBe(expectedColor);
			}
		});
	});

	it("returns an empty array for an empty FEN code", () => {
		const result = parseFenPosition("");
		expect(result).toEqual([]);
	});

	it("throws an error for an invalid piece notation", () => {
		const invalidFenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNX";
		expect(() => parseFenPosition(invalidFenPosition)).toThrow("Invalid Fen Position");
	});

	it("throws an error for a fen position exceeding 8 cols", () => {
		const invalidFenPosition = "rnbqkbnr/pppppppp/9/9/9/9/PPPPPPPP/RNBQKBNX";
		expect(() => parseFenPosition(invalidFenPosition)).toThrow("Invalid Fen Position");
	});

	it("throws an error for a fen position subceeding 8 cols", () => {
		const invalidFenPosition = "rnbqkbnr/pppppppp/7/7/7/7/PPPPPPPP/RNBQKBNX";
		expect(() => parseFenPosition(invalidFenPosition)).toThrow("Invalid Fen Position");
	});

	it("throws an error for a fen position exceeding 8 rows", () => {
		const invalidFenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNX/8";
		expect(() => parseFenPosition(invalidFenPosition)).toThrow("Invalid Fen Position");
	});

	it("throws an error for a fen position subceeding 8 rows", () => {
		const invalidFenPosition = "rnbqkbnr/pppppppp/7/7/7/7/PPPPPPPP/";
		expect(() => parseFenPosition(invalidFenPosition)).toThrow("Invalid Fen Position");
	});

	it("throws an error for a fen position with incorrect seperator", () => {
		const invalidFenPosition = "rnbqkbnr|pppppppp|8/8|8|8|PPPPPPPP|RNBQKBNR";
		expect(() => parseFenPosition(invalidFenPosition)).toThrow("Invalid Fen Position");
	})
});

describe("isDigitFrom1To8 function", () => {
	it("returns true for valid digits from 1 to 8", () => {
		expect(isDigitFrom1To8("1")).toBe(true);
		expect(isDigitFrom1To8("2")).toBe(true);
		expect(isDigitFrom1To8("3")).toBe(true);
		expect(isDigitFrom1To8("4")).toBe(true);
		expect(isDigitFrom1To8("5")).toBe(true);
		expect(isDigitFrom1To8("6")).toBe(true);
		expect(isDigitFrom1To8("7")).toBe(true);
		expect(isDigitFrom1To8("8")).toBe(true);
	});

	it("returns false for invalid digits", () => {
		expect(isDigitFrom1To8("0")).toBe(false);
		expect(isDigitFrom1To8("-1")).toBe(false);
		expect(isDigitFrom1To8("9")).toBe(false);
		expect(isDigitFrom1To8("a")).toBe(false);
		expect(isDigitFrom1To8("")).toBe(false);
		expect(isDigitFrom1To8("12")).toBe(false);
		expect(isDigitFrom1To8("abc")).toBe(false);
		expect(isDigitFrom1To8(" ")).toBe(false);
	});

	it("returns false for non-string input", () => {
		// Test with boolean
		expect(isDigitFrom1To8(true as any)).toBe(false);

		// Test with undefined and null
		expect(isDigitFrom1To8(undefined as any)).toBe(false);
		expect(isDigitFrom1To8(null as any)).toBe(false);
	});
});