# Connect-4

> A simple Connect 4 game, played in the console against a friend or a simple AI.

## About
The aim of this project is to further my familiarity with the basics of C++ and game logic.
* **Standard:** C++20
* **Build System:** CMake 3.20+

## How to build
* It's recommended to create a separate build folder and run cmake from there.
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
### How to play

* Run the executable.
* Choose a game mode – singleplayer (1) or multiplayer (2).
* Enter the column number to drop your piece.

## What I learned

* Separation of concerns (Game v. AI v. Board)
* How to use the enum class (TileState)
* How to use the std::vector (Managing empty spaces)