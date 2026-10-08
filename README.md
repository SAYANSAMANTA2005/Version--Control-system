# Text Version Control System

A basic command-line Version Control System for storing text states,
viewing history, and performing undo operations.

## Current Project State

The project currently provides a simple CLI-based text history system.

### Current Features

-   Accepts text input from the user through the terminal.
-   Stores each entered text as a `State`.
-   Each state has:
    -   A state ID
    -   The text associated with that state
-   Maintains the states in an in-memory `vector<State>`.
-   Displays the current text history.
-   Supports an **Undo** operation.
-   Saves the current history to `history.txt` when the program exits.
-   Saves the current history index to `CurrentIndex.txt`.
-   Loads the previous history when the program starts.
-   Restores the previous current index after restarting the program.
-   Uses a batch script to compile and run the application.

## How to Run

The first line of this README is the command required to run the project
from PowerShell:

``` powershell
.\Script.bat
```

The script:

1.  Compiles `Text.cpp`.
2.  Uses C++17.
3.  Creates `Text.exe`.
4.  Runs the executable.

## Current Project Structure

``` text
Version-Control-system/
│
├── .vscode/
│
├── Text.cpp
├── Text.exe
├── Script.bat
│
├── history.txt
├── CurrentIndex.txt
│
├── main.cpp
├── main.exe
│
├── README.md
└── .gitignore
```

## How the Current System Works

The basic flow is:

``` text
User enters text
       ↓
Create State
       ↓
Store State in vector<State>
       ↓
Increase current index
       ↓
Save history when program exits
```

### State

The current state structure is:

``` cpp
struct State {
    int id;
    string text;
};
```

### In-Memory History

States are stored using:

``` cpp
vector<State> history;
```

The current index is tracked using:

``` cpp
int currIndex;
```

## Persistence

The project currently uses two files for persistence.

### `history.txt`

Stores the text of each state, one state per line.

Example:

``` text
Hello
Hello World
Hello World!
```

### `CurrentIndex.txt`

Stores the current history index.

Example:

``` text
3
```

When the program starts:

``` text
CurrentIndex.txt
       ↓
   Load index
       ↓
history.txt
       ↓
Load text states
       ↓
Restore history
```

## Current Undo Behaviour

When the user selects the Undo option:

``` text
State 0 → State 1 → State 2
                       ↑
                    current
```

Undo moves the current index backward and removes the last state from
the current in-memory history.

For example:

``` text
Before Undo:

State 0 → State 1 → State 2

After Undo:

State 0 → State 1
```

### Important Current Limitation

The current implementation uses:

``` cpp
history.pop_back();
```

during Undo.

Therefore, the undone state is currently removed from the in-memory
history. A proper redo mechanism has not yet been implemented.

## Current Limitations

The current implementation is an early prototype and does not yet
provide all features of a complete Version Control System.

Currently:

-   Redo is not implemented.
-   Undo removes the latest state instead of only moving a current-state
    pointer.
-   States store complete text rather than differences/diffs.
-   Branching is not implemented.
-   Checkout is not implemented.
-   Merge is not implemented.
-   There is no commit/message system.
-   Text input currently supports one line at a time.
-   History is saved when the program exits rather than after every
    state change.
-   Each version is not currently stored as an individual version
    object/file.
-   There is no conflict-resolution mechanism.

## Planned Improvements

The planned development path is:

``` text
Current Prototype
       ↓
Improve Undo
       ↓
Redo
       ↓
Better State Management
       ↓
Commit System
       ↓
Persistent Version Storage
       ↓
Diff-Based Storage
       ↓
Version Graph / DAG
       ↓
Branching
       ↓
Checkout
       ↓
Merge
```

## Long-Term Goal

The goal of this project is to build a lightweight, educational Version
Control System specialized for text.

The system is intended to demonstrate concepts such as:

-   State management
-   History tracking
-   Undo/Redo
-   Persistence
-   File I/O
-   Versioning
-   Diff storage
-   Branching
-   Version graphs
-   Checkout
-   Merge

The project will gradually evolve from the current snapshot-based
prototype into a more complete Git-like version-control system for text.
