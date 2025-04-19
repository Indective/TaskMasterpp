# TaskMaster++ — Modular Task Manager


## 🧠 Project Goal

Build a terminal-based multi-user task manager written in C++, supporting:
- Task creation, editing, deletion
- User account management with password protection
- JSON file storage for tasks and users
- Plugin system for extensibility
- Clean command-line interface

---

## 🔧 Core Modules

### TaskManager
Handles everything related to tasks:
- Create new tasks
- Edit existing tasks
- Mark tasks as complete/incomplete
- Delete tasks
- List all tasks

### UserManager
Handles:
- User account creation
- User login/logout
- Session tracking (which user is active)

### PluginLoader
- Scans the `plugins/` folder for optional features
- Loads plugins at runtime (start with just `.cpp` modules and expand later)
- Each plugin is optional and modular

### CryptoUtils
- Hashes passwords (using SHA-256 or another method)
- Verifies passwords on login

### CommandParser (TBD)
- Parses command-line arguments like:
  - `add "Do homework" --due 2025-04-20`
  - `list --priority high`
  - `user login indective`

---

## 📂 Data Format

### User file (JSON):
```json
{
  "username": "muhammad",
  "password_hash": "a7d91a...", 
  "tasks": ["tasks/muhammad_task1.json", "tasks/muhammad_task2.json"]
}

Task file (JSON):

{
  "title": "Build TaskMaster++",
  "due": "2025-04-20",
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

✅ Milestones

- Set up folder and build structure with CMake

- Add and test nlohmann/json include

- Implement basic TaskManager

- Implement UserManager (with login/register)

- Save/load tasks per user using JSON

- Add command-line interface

- Add plugin system support

- First plugin (e.g., daily motivational quote)

- Build release binary and README

---

## 🧪 Future Ideas

- Unit tests using Catch2

- Full password encryption (PBKDF2 or bcrypt)

- Export/import task backups

- Auto sync to cloud (experimental)

- Task sync to mobile (future idea, maybe with QR codes or text export)

---

## 💬 Notes

- Project should be able to run on any Linux terminal

- Keep all dependencies header-only or simple to build

- Build should work with cmake and make

- Focus on modularity: each part of the code should be reusable and clean

---