# Arcade-
A command-line multi-game system written in C featuring classic board games.  Includes Monopoly (Bankruptcy Edition) where players compete to drive their  opponent bankrupt, and Scotland Yard. Simple menu-driven interface with  turn-based gameplay mechanics.

# Multi-Game System

A command-line multi-game system written in C featuring classic board games. Includes Monopoly (Bankruptcy Edition) where players compete to drive their opponent bankrupt, and Scotland Yard. Simple menu-driven interface with turn-based gameplay mechanics.

## Features

- **Monopoly (Bankruptcy Edition)** - Buy properties, collect rent, and bankrupt your opponent
- **Scotland Yard** - Hunt down the criminal in this strategic chase game
- **Turn-based gameplay** - Easy to follow turn-by-turn mechanics
- **Menu-driven interface** - Simple navigation between games

## Requirements

- C compiler (gcc, clang, or any standard C compiler)
- Windows, macOS, or Linux

## Compilation

```bash
gcc game.c -o game
```

Or with other compilers:
```bash
clang game.c -o game
cc game.c -o game
```

## Running the Game

```bash
./game
```

Or on Windows:
```bash
game.exe
```

## How to Play

### Main Menu
When you start the game, you'll see a menu with options to:
1. Play Monopoly (Bankruptcy Edition)
2. Play Scotland Yard
3. Exit

### Monopoly (Bankruptcy Edition)
- **Starting Money**: $1,000 per player
- **GO Reward**: $200 when passing GO
- **Objective**: Drive your opponent bankrupt
- **Gameplay**:
  - Players take turns rolling dice
  - Move around the board based on dice roll
  - Land on unowned properties to buy them
  - Land on opponent's properties to pay rent
  - First player to go bankrupt loses

### Scotland Yard
- Strategic pursuit game
- Navigate the board to catch or evade the criminal
- Follow the on-screen instructions for each turn

## Game Controls

- Enter numeric choices from the menu
- Press ENTER to roll the dice or advance turns
- Follow prompts for game-specific actions

## File Structure

```
game.c          - Main game file containing all source code
README.md       - This file
```

## Notes

- The game uses `srand(time(0))` to seed random number generation for dice rolls
- Screen clears between turns for better readability
- Input validation prevents common errors like entering non-integer choices

## Future Enhancements

- More game options
- Multiplayer support for more than 2 players
- Saving/loading game state
- More sophisticated AI opponents
