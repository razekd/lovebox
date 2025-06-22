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
  const { to, text, title } = req.body;
  await Message.create({ to, from: req.user.username, text, title });
  res.json({ success: true });
});

// Mark message as read
router.patch("/:id/read", authMiddleware, async (req, res) => {
  const { id } = req.params;
  try {
    const message = await Message.findById(id);

    if (!message) {
      return res.status(404).json({ error: "Message not found" });
    }

    if (message.to !== req.user.username) {
      return res.status(403).json({ error: "Unauthorized" });
    }

    message.read = true;
    await message.save();

    return res.json({ success: true, message });
  } catch (err) {
    console.error(err);
    return res.status(500).json({ error: "Error updating message" });
  }
});

// Fetch all unread messages for the user
router.get("/unread", authMiddleware, async (req, res) => {
  try {
    const messages = await Message.find({
      to: req.user.username,
      read: false,
    }).sort({ timestamp: 1 });

    res.json({
      messages,
      count: messages.length,
    });
  } catch (err) {
    res.status(500).json({ error: "Error fetching unread messages" });
  }
});

// Fetch latest message for the user (by timestamp)

router.get("/latest", authMiddleware, async (req, res) => {
  try {
    const latestMessage = await Message.findOne({
      to: req.user.username,
    })
      .sort({ timestamp: -1 })
      .limit(1);

    if (!latestMessage) {
      return res.status(404).json({ error: "No messages found" });
    }

    res.json(latestMessage);
  } catch (err) {
    res.status(500).json({ error: "Error fetching latest message" });
  }
});

module.exports = router;
