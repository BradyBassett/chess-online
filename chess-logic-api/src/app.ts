import express from "express";
import cors from "cors";
import { boardRouter } from "./routes/boardRouter";

const app = express();
app.use(express.json());
app.use(cors());
app.use("/api/board", boardRouter);

app.listen(3001, () => {
  console.log("Server is running on port 3001");
});

export default app;

// TODO - Eventually will need to get rid of this directory (Chess-logic-api) for now use it for reference.
