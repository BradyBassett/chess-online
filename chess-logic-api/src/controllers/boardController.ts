import { Request, Response } from "express";
import { createBoard, getBoard, updateBoard } from "../services/boardService";


export async function createBoardController(req: Request, res: Response) {
	const fenPosition = req.body.fenPosition as string;
	
	if (!fenPosition) {
		res.status(400).json({ error: "fenPosition is required" });
		return;
	}

	const board = await createBoard(fenPosition);
	res.json(board.toJSON());
}

export async function getBoardController(req: Request, res: Response) {
	try {
		const board = await getBoard();
		res.json(board.toJSON());
	} 
	catch (error) {
		const message = (error instanceof Error) ? error.message : 'An unknown error occurred';
		res.status(400).json({ error: message });
	}
}

export async function updateBoardController(req: Request, res: Response) {
	const selectedSquare = req.body.selectedSquare as { row: number, col: number };
	const destinationSquare = req.body.destinationSquare as { row: number, col: number };

	try {
		const updatedBoard = await updateBoard(selectedSquare, destinationSquare);
		res.json(updatedBoard.toJSON());
	} 
	catch (error) {
		const message = (error instanceof Error) ? error.message : 'An unknown error occurred';
		res.status(400).json({ error: message });
	}
}
