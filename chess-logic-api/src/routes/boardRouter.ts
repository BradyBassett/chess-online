import express from "express";
import { createBoardController, getBoardController, updateBoardController } from "../controllers/boardController";

export const boardRouter = express.Router();

boardRouter.post("/", createBoardController);
boardRouter.get("/getBoard", getBoardController);
boardRouter.patch("/updateBoard", updateBoardController);
