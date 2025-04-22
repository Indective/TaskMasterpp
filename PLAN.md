# TaskMaster++ — Modular Task Manager


## 🧠 Project Goal

Build a terminal-based multi-user task manager written in C++, supporting:
- Task creation, editing, deletion
- User account management with password protection
- JSON file storage for tasks and users
- Plugin system for extensibility
- Clean command-line interface

---

## 📂 Data Format

## Task file (JSON):

{
  "task name": "Build TaskMaster++",
  "due": "2025-04-20",
  "task des": "Terminal based task manager",
  "priority": "high",
  "completed": false
}
```
---

## 🧩 Plugin Ideas

- 💧 Water Reminder
Sends a notification every few hours to drink water.

- 📈 Daily Stats Logger
Logs how many tasks were done per day.

- 🧘‍♂️ Focus Mode
Temporarily locks distractions (could use other terminal tricks).

- 🧠 Motivational Quote Plugin
Displays a new quote every time you open the app.

---