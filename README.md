## Minesweeper in C

A simple Minesweeper game implemented in C.

## Compilation and Running
To build and run the game, navigate to the source folder and run:
```
make
./minesweeper
```

## Controls
- Left click: Reveal a cell
- Right click: Place or remove a flag
- F: Toggle peek mode

## Saving and Loading
You can save your current game state at any time by pressing S. This will create a file called `lsave.bat` containing the current state of the board.

To load a saved game, start the program with the `-f` option:
```
./minesweeper -f lsave.bat
```
This will reconstruct a previously saved view of your game as it was saved.
