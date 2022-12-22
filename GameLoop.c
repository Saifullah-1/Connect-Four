#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "GameLoop.h"

int rows = 9;
int colmns = 7;
char board[/*rows=*/9][/*colmns=*/7]; // read dimentions from xml file
int player_turn_arr[/*rows*colmns*/ 9 * 7];
int turn = 0;
int ColumnFreeSpacesArr[/*colmns*/ 7];
typedef struct
{
    int PlayerScore;
    int PlayerMoves;
    char PlayerName[500];
} Player;
Player Player1 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player1 symbol X and blue color
Player Player2 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player2 symbol Y and red color

const char Player1Symbol = 'X';
const char Player2Symbol = 'O';

void resetPlayerTurnArr()
{
    for (int i = 0; i < rows * colmns; i += 2)
    {
        player_turn_arr[i] = 1;
        player_turn_arr[i + 1] = 2;
    }
}
void resetColumnFreeSpacesArr() // array for free spaces in each column
{
    for (int i = 0; i < colmns; i++)
    {
        ColumnFreeSpacesArr[i] = rows;
    }
}
void resetPlayerData(void)
{
    Player1.PlayerScore = 0;
    Player2.PlayerScore = 0;
    Player1.PlayerMoves = 0;
    Player2.PlayerMoves = 0;
}
void resetBoard(void) // moves array
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colmns; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard(void) // board
{
    gotoxy(0, 3);
    yellow();
    for (int i = 1; i <= colmns; i++)
    {
        printf(" %c%i ", 31, i);
    }
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < colmns; k++)
        {
            printf("|---");
        }
        printf("|");
        printf("\n");
        for (int j = 0; j < colmns; j++)
        {
            printf("| %c ", board[i][j]);
        }
        printf("|");
        printf("\n");
    }
    for (int k = 0; k < colmns; k++)
    {
        printf("|---");
    }
    printf("|");
    printf("\n");
}
int checkFreeSpaces() // free spaces in board  if free spaces == 0 game ends
{
    int freeSpaces = rows * colmns;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colmns; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return (freeSpaces);
}
void checkColumnFreeSpaces(int column_index) // column_index = column number - 1
{
    for (int i = 0; i < rows; i++)
    {
        if (board[i][column_index] != ' ')
        {
            ColumnFreeSpacesArr[column_index]--;
        }
    }
}
// Human vs Human Mode
void playerMove()
{
    int columnNumber; // user input
    int r;
    do
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                      ");
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("Enter Column Number : ");
        scanf("%d", &columnNumber);
        if (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > colmns)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                      ");
        }
        else
        {
            checkColumnFreeSpaces(columnNumber - 1);
            r = ColumnFreeSpacesArr[columnNumber - 1] - 1;
            if (player_turn_arr[turn] == 1)
            {
                board[r][columnNumber - 1] = Player1Symbol;
                turn++;
                Player1.PlayerMoves++;
                break;
            }
            else
            {
                board[r][columnNumber - 1] = Player2Symbol;
                turn++;
                Player2.PlayerMoves++;
                break;
            }
            ColumnFreeSpacesArr[columnNumber - 1]--;
        }
    } while (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > colmns);
}

// VS computer
void computerMove()
{
}
void checkScore()
{
    // horizontal
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colmns; j++)
        {
            if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3])
            {
                if (board[i][j] == Player1Symbol)
                {
                    Player1.PlayerScore++;
                }
                else if (board[i][j] == Player2Symbol)
                {
                    Player2.PlayerScore++;
                }
            }
        }
    }
    // vertical
    for (int i = 0; i < colmns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j])
            {
                if (board[i][j] == Player1Symbol)
                {
                    Player1.PlayerScore++;
                }
                else if (board[i][j] == Player2Symbol)
                {
                    Player2.PlayerScore++;
                }
            }
        }
    }
    // diagonal
}
void playerData()
{
    yellow();
    if (player_turn_arr[turn] == 1 || player_turn_arr[turn] == 2)
    {
        gotoxy(23 + (colmns)*4, 3);
        printf("Player %i Turn", player_turn_arr[turn]);
    }
    else
    {
        gotoxy(23 + (colmns)*4, 3);
        printf("Computer Turn");
    }
    gotoxy(23 + (colmns)*4, 6);
    printf("Number of moves of Player1 : %i", Player1.PlayerMoves);
    gotoxy(23 + (colmns)*4, 9);
    printf("Number of moves of Player2 : %i", Player2.PlayerMoves);
    gotoxy(23 + (colmns)*4, 12);
    printf("Player1 score: %i", Player1.PlayerScore);
    gotoxy(23 + (colmns)*4, 15);
    printf("Player2 score: %i", Player2.PlayerScore);
    gotoxy(23 + (colmns)*4, 18);
    printf("Time passed: %i"); // time function
    reset();
}
