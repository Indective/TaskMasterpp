# Taskmaster++

Taskmaster++ is a terminal-based task management application written in modern C++. It enables users to securely register and log in, manage their personal tasks via a JSON-based system, and maintain persistent task data in a simple and modular architecture.

## 🧠 Features

- 🔒 **User Authentication** — Secure account creation and login using bcrypt password hashing.
- 📋 **Task Management** — Add, list, complete, and save tasks per user.
- 💾 **Persistent Storage** — Stores all data on disk in structured JSON format.
- 🧱 **Modular Design** — Organized source code with headers and implementation separated cleanly.
- ⚙️ **CMake Build** — Fully CMake-integrated for easy cross-platform building.

## 📁 Project Structure

``` html
├── build                  # CMake build output
├── CMakeLists.txt         # Build configuration
├── data                   # User-specific task data
│   └── users
│       ├── indective/     #example test unit
│       └── muhammad/      #example test unit 
|
├── include                # Header files
│   ├── bcrypt.h
│   ├── json.hpp
│   └── taskmaster.hpp
├── src                    # Source code
│   ├── bcrypt/
│   ├── main.cpp
│   ├── taskmanager.cpp
│   └── usermanager.cpp
└── README.md              # This file
```

## ⚙️ Build Instructions

### 📦 Requirements

- C++17-compatible compiler (e.g., `g++`, `clang++`)
- [CMake](https://cmake.org/download/) (version 3.10+)

### 🛠️ Building

```bash
git clone https://github.com/yourusername/taskmasterpp.git
cd taskmasterpp
mkdir build && cd build
cmake ..
make
```

### ▶️ Running

```bash
./tsm
```

## 🚀 Usage

- When launched, the app prompts you to **register** or **log in**.
- Upon successful login, access your personal task list:
  - `Add` tasks
  - `Mark` them as completed
  - `View` or review old ones
- Tasks are saved in:

```  html
  data/users/<username>/tasks.json
```

## 🛠️ Tech Stack

- **C++17**
- **CMake**
- **nlohmann/json** (for parsing JSON)
- **Bcrypt-cpp** (for password hashing)

## 📄 License

This project is released under the **MIT License**. See the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to open issues or submit pull requests to suggest improvements or new features.
