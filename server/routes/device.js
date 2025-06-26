const express = require("express");
const jwt = require("jsonwebtoken");
const User = require("../models/User");
const bcrypt = require("bcrypt");
const router = express.Router();

router.post("/login", async (req, res) => {
  const { deviceId, password } = req.body;
  const user = await User.findOne({ deviceId });
  const isMatch = bcrypt.compare(password, user.passwordHash);
  if (!user || !isMatch) {
    return res.status(401).json({ error: "Unauthorized" });
  }

  const token = jwt.sign({ username: user.username }, process.env.JWT_SECRET, {
    expiresIn: "12h",
  });
  res.json({ token });
});

router.post("/status", async (req, res) => {
  const token = req.headers.authorization?.split(" ")[1];
  if (!token) return res.status(401).json({ error: "Missing token" });

  try {
    const utcNow = new Date(Date.now());
    const { username } = jwt.verify(token, process.env.JWT_SECRET);
    await User.updateOne({ username }, { lastSeen: utcNow });
    res.json({ ok: true });
  } catch {
    res.status(401).json({ error: "Invalid token" });
  }
});

router.get("/status/:username", async (req, res) => {
  const user = await User.findOne({ username: req.params.username });
  if (!user) return res.status(404).json({ error: "User not found" });

  const isOnline = Date.now() - new Date(user.lastSeen).getTime() < 60000;
  res.json({ online: isOnline });
});

module.exports = router;
