# Connect Four Game :video_game:

This repository contains the source code and files for a Connect Four game developed as a final project for the first year in Computer Science and Engineering Department (CSED). The game was created in C programming language and aims to provide an interactive gaming experience.

## 🎯 Team Members :busts_in_silhouette:
- AhmedIAshraf (GitHub: [AhmedIAshraf](https://github.com/AhmedIAshraf))
- Saifullah (GitHub: [Saifullah-1](https://github.com/Saifullah-1))

## 💡 Game Description :page_facing_up:

Connect Four is a two-player game in which the players first choose a color and then take turns dropping their colored discs from the top into a grid. The pieces fall straight down, occupying the next available space within the column. The objective of the game is to connect four of one's own discs of the same color next to each other vertically, horizontally, or diagonally. The two players keep playing until the board is full. The winner is the player with a greater number of connected fours. For more information, you can refer to [Wikipedia](https://en.wikipedia.org/wiki/Connect_Four).

### 📜 Game Overview

The goal of the game is to connect four discs of the same color next to each other vertically, horizontally, or diagonally. The board may be of any size. Each player is assigned a random different color. The score is calculated based on the number of connected fours. The game ends when the board is full. The winner is the player with the highest score. The map is a two-dimensional grid with initially no discs. Each player can select a column to drop a disc, and the players should connect four discs to win.

### 🎮 Game Mode

The game offers two modes:

- Two-player mode: Human vs. Human
- One-player mode: Human vs. Computer

The first player is represented by X with red color, and the second player is represented by O with blue color.

### 🖥️ User Interface

During gameplay, the following information should be displayed beside the grid:

- Whose turn it is
- Number of moves for each player
- Scores of each player
- Time passed in minutes and seconds

### 🏆 User's Rank

When a player successfully wins a game, their name, score, and rank should be recorded. The player's name is case insensitive. High scores should be stored sorted in a file and loaded when the game starts. If the player records a score higher than any of the high scores, the new high score is recorded in the high scores file, and then all high scores are displayed sorted. If it's the first time for the player, they should be added to the scores list. Otherwise, the score should be updated if the current score is higher than the saved score. The game can print the highest X scores, where X is a parameter given as input when the game starts.

### ⚙️ Game Parameters

The game parameters include:

- Board's height
- Board's width
- Maximum number of high scores (size of the high scores list)

The configurations file should be in XML format. Here is a sample configuration file:

```xml
<Configurations>
  <Height>7</Height>
  <Width>9</Width>
  <Highscores>10</Highscores>
</Configurations>
```

for three times, the game will load the default values: Width = 7, Height = 9, Highscores = 10.

### ↩️ Undo and Redo

The player can undo the game until the first move or redo until the last move. After an undo, if the player makes a new move, all redo moves should be cleared.

### 📋 Main Menu

The main menu of the game contains the following options:

- Start a new game: Choose the game mode (vs. human or vs. computer)
- Load a game: Choose a saved game to load
- Top players: View the list of high scores
- Quit: Exit the game

## 🔄 Game Flow

1. Read game parameters from the configuration file. If the file doesn't exist or is corrupted, ask the user for the file path to read it. If loading the file fails multiple times, then load the default values.
2. Show the main menu. For the game mode, ask the user for one or two players and then assign random colors to each player.
3. Loop until the end of the game:
   - Read a move from Player 1.
   - Check if it is valid input and if the selected column has an empty slot.
   - If not valid, ask for another move.
   - Perform the move.
   - Update the user interface and Player 1's score.
   - Repeat the same logic for Player 2. If it is "human vs. computer," then instead of reading the move as input, you should execute some logic for the computer's turn.
4. Update the list of high scores if necessary and display the sorted list of high scores at the end of the game.
5. Ask the player to either go back to the menu or exit.

