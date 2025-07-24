# Pick Up Sticks Game

## Authors



## Overview

This project is a digital version of the classic "Pick Up Sticks" game, implemented in C++ using the SFML graphics library. The objective is to pick up all the sticks as quickly as possible, maximizing your score before the timer runs out.

## Gameplay

- **Goal:** Remove all sticks from the board before time runs out.
- **Scoring:** Each stick color has a different point value (Blue is highest, then Green, Red, Yellow, Purple).
- **Rules:** You can only pick up sticks that are not covered by any other stick.
- **Timer:** Each stick adds 2 seconds to the total game time.

## Features

- Interactive graphical interface (SFML)
- Save and load game state
- Score tracking and timer
- End screens for win, loss, save, and exit
- Help and exit buttons

## Data Structures

- **Sticks:** Stored in a `std::list` for efficient removal.
- **Color Map:** `std::map<std::string, std::vector<Stick*>>` for quick access to sticks by color.
- **Stick Relationships:** Each stick tracks which sticks are above (`std::unordered_set`) and below (`std::vector`) it for fast validity checks.

## Main Classes

- **Controller:** Manages the main game loop and menu.
- **Board:** Handles game logic and stick management.
- **TopBar:** Displays timer, score, and stick counts.
- **SideBar:** Manages help, save, and exit buttons.
- **EndScreen:** Displays end-of-game messages.
- **Stick:** Represents a single stick and its logic.
- **FileDealing:** Handles saving/loading game state.
- **Resources:** Singleton for managing textures, fonts, and window.

## Save File

- Game state is saved to a text file (`saveFile.txt`).
- The file must exist for the game to run (due to CMake configuration).
- If you want to test error handling, you can empty or remove the file and observe the exception.

## Build Instructions

### Prerequisites

- C++20 compatible compiler
- [SFML 2.6](https://www.sfml-dev.org/download.php) (ensure the path in `CMakeLists.txt` matches your installation)
- CMake 3.26 or higher

### Building

1. Clone the repository.
2. Make sure SFML is installed and the `SFML_LOCATION` variable in `CMakeLists.txt` points to your SFML directory.
3. Run CMake to configure the project:
   ```sh
   cmake -S . -B build
   ```
4. Build the project:
   ```sh
   cmake --build build
   ```
5. Run the executable from the build directory.

### Notes

- All required resources (images, fonts, save file) are copied to the build directory automatically.
- On Windows, required SFML DLLs are also copied post-build.

## Controls

- **Mouse:** Click on sticks to pick them up (if valid).
- **Side Buttons:** Use Help, Save, and Exit as needed.

## License

This project is for educational purposes. 
