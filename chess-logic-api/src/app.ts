import express from "express";
const app = express();

app.use(express.json());

app.post("/validate-move", (req, res) => {
  const { piece, from, to } = req.body;

  res.json(
    { 
      status: "success",
      message: `Validating move for ${piece} from ${from} to ${to}`,
    }
  );
});

const port = process.env.port || 3001;
app.listen(port, () => {
  console.log(`Express app listening at http://localhost:${port}`);
});
