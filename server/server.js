const express = require("express");
const bodyParser = require("body-parser");

const app = express();
app.use(bodyParser.json());

let message = "Hello from Lovebox!"; // Default message

// GET: Retrieve the current message
app.get("/api/message", (req, res) => {
  console.log("✅ Request received from:", req.ip);
  res.json({ message });
});

// POST: Update the message
app.post("/api/message", (req, res) => {
  message = req.body.message || message;
  res.json({ success: true, newMessage: message });
});

const PORT = 3000;
app.listen(PORT, "0.0.0.0", () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
