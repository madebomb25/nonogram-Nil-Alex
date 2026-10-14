# Terminal Nonogram Game

An interactive, terminal-based Nonogram game written in C++. Load a puzzle using row and column clues, mark or clear cells, and solve it directly from the command line.

## Overview

A Nonogram is a logic puzzle in which numerical clues describe consecutive groups of filled cells in each row and column. Groups must appear in the specified order, with at least one empty cell between them.

This program displays the board and its clues, processes player commands, and checks whether the current board satisfies all row and column constraints.

## Features

- Configurable board dimensions.
- Custom row and column clues supplied through standard input.
- Text-based board display with numbered rows and columns.
- Commands to mark or clear individual cells and rectangular areas.
- Board reset and display commands.
- Automatic solution validation after each marking or clearing command.
- Move counter and end-of-game messages.

## Implementation

The project uses:

- `vector<vector<char>>` to represent the board.
- `vector<vector<unsigned int>>` to store row and column clues.
- Separate functions for input, board rendering, player actions, and solution validation.
- A shared validation function for both rows and columns.

Board cells have two states:

- `.` — unmarked cell.
- `X` — filled cell.

There is no separate state for cells explicitly identified as empty.

## Requirements

- A C++ compiler, such as `g++`.
- A terminal.

The program uses the C++ standard library and requires no external dependencies.

## Build and Run

Assuming the source file is named `codi.cc`:

```bash
g++ -std=c++11 -Wall -Wextra codi.cc -o nonogram
./nonogram
```

To run the program using an input file:

```bash
./nonogram < input.txt
```

## Puzzle Input Format

First, enter the number of rows and columns:

```text
<number_of_rows> <number_of_columns>
```

Next, enter the clues for each row, followed by the clues for each column.

Each clue sequence starts with the number of groups, followed by their lengths:

```text
<number_of_groups> <group_1_length> <group_2_length> ...
```

Examples:

```text
2 3 1
```

This describes two groups: one containing three filled cells and another containing one filled cell.

```text
0
```

This describes a row or column with no filled cells.

## Commands

Coordinates are 1-based and must be entered in row–column order.

| Command | Format | Action |
|---------|--------|--------|
| `A` | `A row column` | Mark a cell as filled. |
| `E` | `E row column` | Clear a filled cell. |
| `B` | `B start_row start_column end_row end_column` | Mark every cell in an inclusive rectangular area. |
| `F` | `F start_row start_column end_row end_column` | Clear every cell in an inclusive rectangular area. |
| `R` | `R` | Clear the board and reset the move counter. |
| `S` | `S` | Display the current board and clues. |
| `Z` | `Z` | Exit the game. |

For rectangular commands, the starting row and column must not exceed the ending row and column.

Each `A`, `B`, `E`, or `F` command counts as one move, even if it does not change any cells. Displaying the board does not count as a move.

## Example

The following input defines a 3 × 3 puzzle whose solution is a cross, then solves it in two moves:

```text
3 3
1 1
1 3
1 1
1 1
1 3
1 1
B 1 2 3 2
B 2 1 2 3
```

The first three clue sequences describe the rows; the next three describe the columns.

The completed board is:

```text
.X.
XXX
.X.
```

When the puzzle is solved, the program displays the final board, a congratulatory message, and the move count.

## Game Flow

1. Read the board dimensions and clues.
2. Display the initially empty board.
3. Process player commands.
4. Check the solution after each marking or clearing command.
5. End the game when the puzzle is solved or the player enters `Z`.

Use `S` to view the board during play. The board is also displayed automatically at the start of the game and when the puzzle is solved.

## Limitations

- Input is assumed to be valid: dimensions must be positive, coordinates must be within bounds, and commands must follow the expected format.
- The program does not generate puzzles or solve them automatically.
- It checks whether the current board satisfies the clues, but does not verify whether a puzzle has a unique solution.
- Terminal alignment is designed primarily for small boards.
- Interface messages are currently in Catalan, while source-code comments are primarily in Spanish.

## Learning Outcomes

This project demonstrates practical use of:

- Two-dimensional vectors and matrix traversal.
- Modular programming with functions.
- References and const references.
- Standard input and output.
- Command-driven interaction and game-state management.
- Sequential validation of consecutive cell groups.
