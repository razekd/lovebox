const mongoose = require("mongoose");

const userSchema = new mongoose.Schema({
  username: String,
  passwordHash: String,
  deviceId: String,
  lastSeen: Date,
});

module.exports = mongoose.model("User", userSchema);
