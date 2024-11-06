# Quoridor Game Project

This repository contains the implementation of the Quoridor board game, designed as a project for the Fall 2023 course. The game can be played by 2 to 4 players, with the objective of reaching the opposite side of the board while strategically placing walls to hinder the opponent.

## Game Overview

Quoridor is a strategic board game where each player controls a pawn and a set number of walls. The goal is to move your pawn to the opposite side of the board before your opponent does. Players can either move their pawn or place a wall to block the opponent's path.

## Project Phases

### Phase 1: Map Creation (10%)

- Implement the game board using ASCII characters.
- Input includes board dimensions, player positions, and wall details.
- Example input format:

  10
  0 1
  7 3
  1
  1 1 H
  1
  5 5 V


### Phase 2: Gameplay (30%)

- Implement the mechanics for a two-player game.
- Players alternate turns, choosing to move their pawn or place a wall.
- Ensure that walls do not completely block a player from reaching their goal.

### Phase 3: Play Against Computer (15%)

- Implement AI decisions using random functions while adhering to game rules.
- Allow players to choose to play against the computer.

### Phase 4: Save and Load Game (15%)

- Enable players to save their game progress and load it to continue later.

### Phase 5: Spells and Rewards (30%)

- Introduce random magical boxes containing spells or rewards.
- Spells include removing walls, reducing wall count, or skipping turns.
- Rewards include increasing wall count or reducing opponent's walls.

## Extra Credit Options

1. **Optimal Pathfinding Algorithms (3%)**: Implement A* or similar algorithms.
2. **AI Intelligence (up to 10%)**: Implement smarter AI using rule-based or Minimax algorithms.
3. **Network Play (15%)**: Enable two-player games over a network.
4. **Four-Player Mode (15%)**: Support four players, with at least one controlled by a user.
5. **Version Control with Git (10%)**: Use Git for version control and teamwork.
6. **Graphical User Interface (15%)**: Develop a GUI for the game.

## Implementation Notes

- The project is to be completed in teams of two.
- Code similarity checks will be conducted, and identical submissions will result in penalties.
- A maximum of 50% extra credit can be earned.
- Code quality and understanding will be assessed, impacting the final grade.

## Getting Started

To get started with this project, clone the repository and follow the instructions for each phase to build the complete game.

```
git clone https://github.com/Roozbehsn/Quoridor-cpp.git
```

For more details on game rules and strategies, refer to the official Quoridor game documentation or use the provided [link](https://drive.google.com/file/d/1Mf1PsQqLaryWDT7hKdYYNDDaKRZ_vthh/view?usp=drive_link) for further learning.
