#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "GameLoop.h"
#include "Menu.c"


int rows = 6;
int colmns = 6;
char board[/*rows=*/6][/*columns=*/6]; // read dimentions from xml file
int player_turn_arr[/*rows*columns+2*/ 6 * 6+2];
int turn = 0;
int ColumnFreeSpacesArr[/*columns*/ 6];

int hours , minutes , seconds ;


void Time (int start , int end)
{
    seconds = (end - start)/CLOCKS_PER_SEC;
    minutes=0 , hours=0 ;
    while(seconds>=60)
    {
        minutes += seconds/60;
        seconds -= minutes*60;
    }
    while (minutes>=60)
    {
        hours += minutes/60;
        minutes %= 60;
    }
}


void Instant_Save(int i , int j)
{
    FILE* Psave;
    Psave = fopen("Save.txt","w");
    fprintf (Psave , "1's Score \t 2's Score\n");
    fprintf (Psave , "%d \t \t %d" ,i,j);
    fclose (Psave);
    }

void TopScores(char name[] , int s)    // s refers To Player's Score
{
    FILE* Pscores;
    Pscores = fopen ("Scores.txt","a");
    printf ("%c\t%d",name,s);
    fclose (Pscores);
}



typedef struct
{
    int PlayerScore;
    int PlayerMoves;
    char *PlayerName[100];
} Player;
Player Player1 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player1 red color
Player Player2 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player2 blue color

const char Player1Symbol = 'X';
const char Player2Symbol = 'O';

void resetPlayerTurnArr(void)
{
    for (int i = 0; i < rows * colmns; i += 2)
    {
        player_turn_arr[i] = 1;
        player_turn_arr[i + 1] = 2;
    }
}
void resetColumnFreeSpacesArr(void) // array for free spaces in each column
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
        if (i>9)
        {
            printf(" %i ", i);
        }
        else{
        printf(" %i  ", i);}
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
            printf("|");
            if (board[i][j]==Player1Symbol)
            {
                red();printf(" %c ", board[i][j]);
            }else if (board[i][j]==Player2Symbol)
            {
                LightBlue();printf(" %c ", board[i][j]);
            }else{
                printf(" %c ", board[i][j]);
            }
            yellow();
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
int checkFreeSpaces(void) // free spaces in board  if free spaces == 0 game ends
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

// Human vs Human Mode
void playerMove(void)
{
    int columnNumber; // user input
    int r;
    do
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                      ");
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("Please Enter A Not Full Column Number from 1 to %i : ", colmns);
        scanf("%d", &columnNumber);
        if (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > colmns)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                      ");
        }
        else
        {
            r = ColumnFreeSpacesArr[columnNumber - 1] - 1;
            if (player_turn_arr[turn] == 1)
            {
                board[r][columnNumber - 1] = Player1Symbol;
                turn++;
                Player1.PlayerMoves++;
                ColumnFreeSpacesArr[columnNumber - 1]--;
                break;
            }
            else
            {
                board[r][columnNumber - 1] = Player2Symbol;
                turn++;
                Player2.PlayerMoves++;
                ColumnFreeSpacesArr[columnNumber - 1]--;
                break;
            }
        }
    } while (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > colmns);
}

// VS computer
void computerMove(void)
{
}
void checkScore(void)
{
    // horizontal
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colmns-3; j++)
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
    for (int j = 0; j < colmns; j++)
    {
        for (int i = 0; i < rows-3; i++)
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
    for (int i= 0; i < rows-3 ; i++)
    {
        for (int j = 0; j < colmns-3; j++)
        {
            if (board[i][j] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j+2] && board[i+2][j+2] == board[i+3][j+3])
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
    for (int i = 0; i < rows-3 ; i++)
    {
        for (int j = colmns-3 ; j < colmns ; j++)
        {
            if (board[i][j] == board[i+1][j - 1] && board[i][j] == board[i+2][j - 2] && board[i][j] == board[i+3][j - 3])
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

}
void playerData(void)
{
    yellow();
    if (player_turn_arr[turn] == 1)
    {
        gotoxy(23 + (colmns)*4, 4);red();
        printf("Player %i Turn", player_turn_arr[turn]);
    }else if (player_turn_arr[turn] == 2)
    {
        gotoxy(23 + (colmns)*4, 4);LightBlue();
        printf("Player %i Turn", player_turn_arr[turn]);
    }
    else
    {
        gotoxy(23 + (colmns)*4, 4);
        printf("Computer Turn");
    }
    gotoxy(23 + (colmns)*4, 6);red();
    printf("Number of moves of Player1 : %i", Player1.PlayerMoves);
    gotoxy(23 + (colmns)*4, 7);LightBlue();
    printf("Number of moves of Player2 : %i", Player2.PlayerMoves);
    gotoxy(23 + (colmns)*4, 8);red();
    printf("Player1 score: %i", Player1.PlayerScore);
    gotoxy(23 + (colmns)*4, 9);LightBlue();
    printf("Player2 score: %i", Player2.PlayerScore);
    gotoxy(23 + (colmns)*4, 10);yellow();
    printf("Time passed: %i Hours %i Minutes %i Seconds", hours, minutes, seconds); // time function
    reset();
}
void checkWinner(void){
    if (Player1.PlayerScore>Player2.PlayerScore)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        red();printf("Player1 Won! Please Enter Player1 Name : ");
        fgets(Player1.PlayerName, 100,stdin);
    }else if (Player1.PlayerScore<Player2.PlayerScore)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        LightBlue();printf("Player2 Won! Please Enter Player2 Name : ");
        fgets(Player2.PlayerName, 100,stdin);
    }else
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        reset();printf("Draw! Please Enter Player1 Name : ");
        fgets(Player1.PlayerName, 100,stdin);
        printf("\nPlease Enter Player2 Name : ");
        fgets(Player2.PlayerName, 100,stdin);
    }
    FILE* Posave;
    FILE* Pcsave;
    Posave = fopen("Save.txt","w");
    fprintf (Posave , "%s Score \t Player 2 Score\n");
    fprintf (Posave , "%d \t %d" ,Player1.PlayerScore,Player2.PlayerScore);
    Pcsave = fclose ("Save.txt");
}
