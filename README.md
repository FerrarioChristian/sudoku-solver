# Sudoku Solver & Visualizer

This project was developed to play with practical applications of state-space search algorithms (Backtracking) alongside object-oriented programming principles and GUI development using C++ and Qt. It aims to demonstrate clean code architecture, signal-slot mechanics, and algorithmic visualization.

## Features

- **Interactive GUI:** Intuitive graphical interface built with Qt to input custom Sudoku puzzles or edit existing ones.
- **Step-by-Step Visualization:** Navigate through the solution using Next/Previous step buttons, or use the Auto-Solve (play/pause) feature to watch the puzzle be solved in real-time.
- **Optimized Algorithm:** Recursive backtracking algorithm for efficient and complete problem-solving.

## The Backtracking Algorithm

The core of the solver relies on a **Depth-First Search (DFS) Backtracking Algorithm**. It systematically searches for a solution by:

1. Finding an empty cell on the 9x9 grid.
2. Attempting to place digits `1` through `9` in that cell.
3. Checking if the placed digit is valid according to Sudoku rules (must be unique in its row, column, and 3x3 sub-grid).
4. Recursively attempting to fill the rest of the grid.
5. If a dead end is reached (no valid digit can be placed), the algorithm *backtracks*, clears the current cell, and tries the next possible digit in the previous cell.

Every state change is recorded by the application in memory, allowing the user to scrub backward and forward through the algorithm's entire decision tree visually.

## Getting Started

### Prerequisites

To compile and run this project, you will need:

- A modern C++ compiler (GCC, Clang, or MSVC)
- [Qt Framework](https://www.qt.io/) (Qt 5 or Qt 6)
- `qmake` (included with Qt)
- `make` (or `nmake`/`mingw32-make` depending on your OS)

### Build Instructions

1. **Clone the repository**

   ```bash
   git clone https://github.com/FerrarioChristian/sudoku-solver.git && cd sudoku-solver
   ```

2. **Navigate to the project directory**

   ```bash
   cd SudokuSolver
   ```

3. **Generate the Makefile**

   ```bash
   qmake SudokuSolver.pro
   ```

4. **Compile the project**

   ```bash
   make
   ```

5. **Run the executable**
   - **Linux/macOS:** `./SudokuSolver` (or the equivalent output name depending on your build settings)
   - **Windows:** `release\SudokuSolver.exe` or `debug\SudokuSolver.exe`
