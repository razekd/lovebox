const mongoose = require("mongoose");

const messageSchema = new mongoose.Schema({
  to: String, // username
  from: String,
  text: String,
  title: String,
  timestamp: { type: Date, default: Date.now },
  read: { type: Boolean, default: false },
});

module.exports = mongoose.model("Message", messageSchema);
