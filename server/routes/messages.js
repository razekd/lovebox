const express = require("express");
const jwt = require("jsonwebtoken");
const Message = require("../models/Message");
const router = express.Router();

const authMiddleware = (req, res, next) => {
  const token = req.headers.authorization?.split(" ")[1];
  if (!token) return res.status(401).json({ error: "No token" });

  try {
    req.user = jwt.verify(token, process.env.JWT_SECRET);
    next();
  } catch {
    return res.status(403).json({ error: "Invalid token" });
  }
};

// Web user sends message
router.post("/send", authMiddleware, async (req, res) => {
  const { to, text } = req.body;
  await Message.create({ to, from: req.user.username, text });
  res.json({ success: true });
});

// Device fetches latest message
router.get("/latest", authMiddleware, async (req, res) => {
  const msg = await Message.findOne({
    to: req.user.username,
    read: false,
  }).sort({ timestamp: -1 });
  if (msg) {
    msg.read = true;
    await msg.save();
  }
  res.json({ message: msg || null });
});

module.exports = router;
