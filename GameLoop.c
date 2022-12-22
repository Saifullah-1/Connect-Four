#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "GameLoop.h"
int rows = 9, colmns = 7;
int column_number;
int grid[/*rows=*/9][/*colmns=*/7]; // read dimentions from xml file
int player_turn = 1;
typedef struct
{
    int PlayerScore;
    int PlayerMoves;
    char PlayerName[500];
} Player;
Player Player1 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player1 symbol X and blue color
Player Player2 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player2 symbol Y and red color

void resetPlayerData(void)
{
    Player1.PlayerScore = 0;
    Player2.PlayerScore = 0;
    Player1.PlayerMoves = 0;
    Player2.PlayerMoves = 0;
}
void grid_design(void)
{
    yellow();
    int i, j, k, l, m;
    for (i = 1; i <= colmns; i++)
    {
        gotoxy(4 + (i - 1) * 4, 2);
        printf("%c%i", 31, i);
    }
    for (j = 1; j <= rows + 1; j++)
    {
        gotoxy(3, 3 + (j - 1) * 2);
        for (k = 1; k <= colmns; k++)
        {
            printf("+---");
        }
        printf("+");
    }
    for (l = 1; l <= colmns + 1; l++)
    {
        for (m = 1; m <= rows; m++)
        {
            gotoxy(3 + (l - 1) * 4, 4 + (m - 1) * 2);
            printf("|");
        }
    }
    printf("\n\n");
}

void playerData(void)
{
    yellow();
    if (player_turn == 1 || player_turn == 2)
    {
        gotoxy(23 + (colmns)*4, 3);
        printf("Player %i Turn", player_turn);
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
void scan_column_number(int column, int max, int min)
{
    printf("Enter column number : ");
    scanf("%i", &column_number);
    while (column_number < 1 || column_number > colmns)
    {
        printf("Enter valid column number : ");
        scanf("%i", &column_number);
    }
    int i = 0;
    int k = 0;
    if (i = colmns + 1)
    {
        i = 0;
        k++;
    }
    grid[i++][k] = column_number;
}
void drawing_in_grid(void)
{
}