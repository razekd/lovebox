const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");
require("dotenv").config();

const authRoutes = require("./routes/auth");
const deviceRoutes = require("./routes/device");
const messageRoutes = require("./routes/messages");

const app = express();
app.use(cors());
app.use(express.json());

// Routes
app.use("/api/auth", authRoutes);
app.use("/api/device", deviceRoutes);
app.use("/api/messages", messageRoutes);

// Connect to MongoDB and start server
mongoose.connect(process.env.MONGODB_URI).then(() => {
  console.log("Connected to MongoDB");
  app.listen(3000, () => console.log("Server running on port 3000"));
});
