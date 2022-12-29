#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "GameLoop.h"
typedef struct
{
    int width;
    int height;
    int scores;
} configuration;

int rows = 4;
int colmns = 4;
char board[/*rows=*/4][/*columns=*/4]; // read dimentions from xml file
int position_array[/*rows*colmns*/ 4 * 4];
int player_turn_arr[/*rows*columns+2*/ 4 * 4 + 2];
int turn = 0;
int ColumnFreeSpacesArr[/*columns*/ 4];

int hours, minutes, seconds;
void SaveTop(char s[], int n)
{
    int i = 0;
    FILE *Ptop;
    Ptop = fopen("Scores.txt", "a");
    while (s[i])
    {
        fprintf(Ptop, "%c", tolower(s[i]));
        i++;
    }
    fprintf(Ptop, " : %d\n", n);
    fclose(Ptop);
}

void CheckPlaces()
{
    for (int i=0 ; i<colmns ; i++)
    {
        for (int j =0 ; j<rows ; j++)
        {
            if (board[j][i] == ' ')
            {
                ColumnFreeSpacesArr[i] += 1;
            }
        }
    }
}

void Time(int start, int end)
{
    seconds = (end - start) / CLOCKS_PER_SEC;
    minutes = 0, hours = 0;
    while (seconds >= 60)
    {
        minutes += seconds / 60;
        seconds -= minutes * 60;
    }
    while (minutes >= 60)
    {
        hours += minutes / 60;
        minutes %= 60;
    }
}

void Instant_Save(int i, int j)
{
    FILE *Psave;
    Psave = fopen("Save.txt", "w");
    fprintf(Psave, "1's Score \t 2's Score\n");
    fprintf(Psave, "%d \t \t %d", i, j);
    fclose(Psave);
}

void TopScores(char name[], int s) // s refers To Player's Score
{
    FILE *Pscores;
    Pscores = fopen("Scores.txt", "a");
    printf("%s\t%d", name, s);
    fclose(Pscores);
}

typedef struct
{
    int PlayerScore;
    int PlayerMoves;
    char PlayerName[100];
} Player;
Player Player1 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player1 red color
Player Player2 = {.PlayerScore = 0, .PlayerMoves = 0}; // Player2 blue color

const char Player1Symbol = 'X';
const char Player2Symbol = 'O';

void resetPlayerTurnArr(int mode)
{
    for (int i = 0; i < rows * colmns + 2; i += 2)
    {
        player_turn_arr[i] = 1;
        player_turn_arr[i + 1] = mode;
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
    turn = 0;
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
        if (i > 9)
        {
            printf(" %i ", i);
        }
        else
        {
            printf(" %i  ", i);
        }
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
            if (board[i][j] == Player1Symbol)
            {
                red();
                printf(" %c ", board[i][j]);
            }
            else if (board[i][j] == Player2Symbol)
            {
                LightBlue();
                printf(" %c ", board[i][j]);
            }
            else
            {
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
        printf("Please Enter A Non Full Column Number from 1 to %i : ", colmns);
        scanf("%d", &columnNumber);
        fflush(stdin);
        if (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > colmns)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                      ");
        }
        else
        {
            position_array[turn] = columnNumber;
            for (int i = turn + 1; i < rows * colmns; i++)
            {
                position_array[i] = 0;
            }
            position_array[turn] = columnNumber;
            r = ColumnFreeSpacesArr[columnNumber - 1] - 1;
            if (player_turn_arr[turn] == 1)
            {
                board[r][columnNumber - 1] = Player1Symbol;
                Player1.PlayerMoves++;
                ColumnFreeSpacesArr[columnNumber - 1]--;
                turn++;
                break;
            }
            else if (player_turn_arr[turn] == 2)
            {
                board[r][columnNumber - 1] = Player2Symbol;
                Player2.PlayerMoves++;
                turn++;
                ColumnFreeSpacesArr[columnNumber - 1]--;
                break;
            }
        }
    } while (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > colmns);
}

// VS computer
void computerMove(void)
{
    /*int found = 0;
    if (turn == 1)
    {
        if (position_array[0] <= colmns - 3)
        {
            board[rows - 1][position_array[0]] = Player2Symbol;
            turn++;
            Player2.PlayerMoves++;
        }
        else if (position_array[0] >= 4)
        {
            board[rows - 1][position_array[0] - 2] = Player2Symbol;
            turn++;
            Player2.PlayerMoves++;
        }
        else
        {
            board[rows - 2][position_array[0] - 1] = Player2Symbol;
            turn++;
            Player2.PlayerMoves++;
        }
    }
    else
    {
        // horizontal
        while (found == 0)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < colmns - 3; j++)
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j] == Player1Symbol)
                    {
                        if (((j + 2) < (colmns - 2)) && board[i][j + 3] == ' ')
                        {
                            board[i][j + 3] = Player2Symbol;
                            turn++;
                            found = 1;
                            Player2.PlayerMoves++;
                        }
                        else if ((j - 1) >= 0 && board[i][j - 1] == ' ')
                        {
                            board[i][j - 1] = Player2Symbol;
                            turn++;
                            found = 1;
                            Player2.PlayerMoves++;
                        }
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < colmns - 1; j++)
                {
                    if (j < colmns - 1 && board[i][j] == Player2Symbol && board[i][j + 1] == ' ')
                    {
                        board[i][j + 1] == Player2Symbol;
                        turn++;
                        found = 1;
                        Player2.PlayerMoves++;
                    }
                    else if (j > 0 && board[i][j] == Player2Symbol && board[i][j - 1] == ' ')
                    {
                        board[i][j - 1] == Player2Symbol;
                        turn++;
                        found = 1;
                        Player2.PlayerMoves++;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
            // vertical
            for (int j = 0; j < colmns; j++)
            {
                for (int i = 0; i < rows - 3; i++)
                {
                    if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i][j] == Player1Symbol)
                    {
                        if (i + 2 < 0 && board[i + 3] == ' ')
                        {
                            board[i][j - 1] == Player2Symbol;
                            turn++;
                            found = 1;
                            Player2.PlayerMoves++;
                        }
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
            for (int j = 0; j < colmns; j++)
            {
                for (int i = rows - 1; i > 0; i--)
                {
                    if (board[i][j] == Player2Symbol && board[i + 1][j] == ' ')
                    {
                        board[i][j + 1] == Player2Symbol;
                        turn++;
                        found = 1;
                        Player2.PlayerMoves++;
                    }
                }
            }
            break;
        }
    }*/
}

void checkScore(void)
{
    // HORIZONTAL
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colmns - 3; j++)
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
    // VERTICAL
    for (int j = 0; j < colmns; j++)
    {
        for (int i = 0; i < rows - 3; i++)
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
    // DIAGONAL
    /*  First Case
        +---+---+---+
        | x |   |   |
        +---+---+---+
        |   | x |   |
        +---+---+---+
        |   |   | x |
        +---+---+---+
    */
    for (int i = 0; i < rows - 3; i++)
    {
        for (int j = 0; j < colmns - 3; j++)
        {
            if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3])
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
    /* Second Case
        +---+---+---+
        |   |   | x |
        +---+---+---+
        |   | x |   |
        +---+---+---+
        | x |   |   |
        +---+---+---+
    */
    for (int i = 0; i < rows - 3; i++)
    {
        for (int j = 3; j <= colmns - 1; j++)
        {
            if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3])
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
    if (turn < colmns * rows)
    {
        if (player_turn_arr[turn] == 1)
        {
            gotoxy(23 + (colmns)*4, 4);
            red();
            printf("Player %i Turn", player_turn_arr[turn]);
        }
        else if (player_turn_arr[turn] == 2)
        {
            gotoxy(23 + (colmns)*4, 4);
            LightBlue();
            printf("Player %i Turn", player_turn_arr[turn]);
        }
        else
        {
            yellow();
            gotoxy(23 + (colmns)*4, 4);
            printf("Computer Turn");
        }
    }
    else
    {
        gotoxy(23 + (colmns)*4, 4);
        printf("                                         ");
        gotoxy(23 + (colmns)*4, 4);
        reset();
        printf("Game Over");
    }

    gotoxy(23 + (colmns)*4, 6);
    red();
    printf("Number of moves of Player1 : %i", Player1.PlayerMoves);
    gotoxy(23 + (colmns)*4, 7);
    LightBlue();
    printf("Number of moves of Player2 : %i", Player2.PlayerMoves);
    gotoxy(23 + (colmns)*4, 8);
    red();
    printf("Player1 score: %i", Player1.PlayerScore);
    gotoxy(23 + (colmns)*4, 9);
    LightBlue();
    printf("Player2 score: %i", Player2.PlayerScore);
    gotoxy(23 + (colmns)*4, 10);
    yellow();
    printf("Time passed: %02i:%02i:%02i", hours, minutes, seconds); // time function
}
void checkWinner(void)
{
    if (Player1.PlayerScore > Player2.PlayerScore)
    {
        red();
        while (1)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("Player1 Won With score %i!\n Please Enter Player1 Name : ", Player1.PlayerScore);
            gets(Player1.PlayerName);
            if (strlen(Player1.PlayerName) != 1)
            {
                SaveTop(Player1.PlayerName, Player1.PlayerScore);
                break;
            }
        }
    }
    else if (Player1.PlayerScore < Player2.PlayerScore)
    {
        LightBlue();
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        while (1)
        {
            printf("Player2 Won With score %i!\n Please Enter Player2 Name : ", Player2.PlayerScore);
            gets(Player2.PlayerName);
            if (strlen(Player2.PlayerName) != 1)
            {
                SaveTop(Player2.PlayerName, Player2.PlayerScore);
                break;
            }
        }
    }
    else
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        reset();
        printf("Draw!\n");
        red();
        while (1)
        {
            gotoxy(0, 9 + (rows - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 9 + (rows - 1) * 2);
            printf("Please Enter Player1 Name : ");
            fgets(Player1.PlayerName, 101, stdin);
            if (strlen(Player1.PlayerName) != 1)
            {
                SaveTop(Player1.PlayerName, Player1.PlayerScore);
                break;
            }
        }
        LightBlue();
        while (1)
        {
            gotoxy(0, 10 + (rows - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 10 + (rows - 1) * 2);
            printf("Please Enter Player2 Name : ");
            fgets(Player2.PlayerName, 101, stdin);
            if (strlen(Player2.PlayerName) != 1)
            {
                SaveTop(Player2.PlayerName, Player2.PlayerScore);
                break;
            }
        }
    }
}
void startGame(void)
{
    char userInput[100];
    while (1)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("Please Enter [1]T0 Start Game >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 == 1)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                                                      ");
            break;
        }
    }
}
int inGameMenu(void) // The Player Choose Either [1]Resume , [2]Undo , [3]Redo , [4]Save The Game Or [5]Exit
{
    int choice;
    char userInput[100];
    while (1)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (rows - 1) * 2);
        if (player_turn_arr[turn] == 1)
        {
            red();
        }
        else
        {
            LightBlue();
        }
        printf("Please Enter [1]Resume....[2]Undo....[3]Redo....[4]Save....[5]Main Menu >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 >= 1 && x - 48 <= 5)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                                                      ");
            choice = x - 48;
            break;
        }
    }
    return (choice);
}
int saveMenu(void)
{
    int choice;
    char userInput[100];
    while (1)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 9 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 10 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("Please Enter The File You Will Save In  [1]File 1....[2]File 2....[3]File 3 >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 >= 1 && x - 48 <= 3)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                                                      ");
            choice = x - 48;
            break;
        }
    }
    return (choice);
}
int afterGame(void) // The Player Chooses After The Game End Either [1]Main Menu Or [2]Exit
{
    int choice;
    char userInput[100];
    while (1)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 9 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 10 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("Please Enter [1]Main Menu....[2]Exit >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 >= 1 && x - 48 <= 2)
        {
            gotoxy(0, 8 + (rows - 1) * 2);
            printf("                                                                                                                                      ");
            choice = x - 48;
            turn++;
            break;
        }
    }
    return (choice);
}
/*------------------------------------------undo and redo----------------------------------------------*/
void resetUndoArray(void)
{
    for (int i = 0; i < colmns * rows; i++)
    {
        position_array[i] = 0;
    }
}
void undo(int game_mode)
{
    if (checkFreeSpaces() < colmns * rows)
    {
        if (game_mode == 2) // vsHuman mode
        {
            int j = position_array[turn - 1] - 1;
            int i = 0;
            while (i < rows)
            {
                if (board[i][j] != ' ')
                {
                    Player1.PlayerScore = 0;
                    Player2.PlayerScore = 0;
                    if (board[i][j] == Player1Symbol)
                    {
                        Player1.PlayerMoves--;
                    }
                    else
                    {
                        Player2.PlayerMoves--;
                    }
                    board[i][j] = ' ';
                    // position_array[turn - 1] = 0;
                    turn--;
                    ColumnFreeSpacesArr[j]++;
                    break;
                }
                i++;
            }
        }
        /*else if (game_mode == 1 && turn >= 2) // vsComputer mode
        {
            int l = position_array[turn - 1] - 1;
            int m = position_array[turn - 2] - 1;
            int k = 0;
            while (k < rows)
            {
                if (board[k][l] != ' ' && board[k][m] != ' ')
                {
                    if (board[k][l] == Player1Symbol)
                    {
                        board[k][l] = ' ';
                    }
                    else if (board[k][m] == Player2Symbol)
                    {
                        board[k][m] = ' ';
                    }
                    Player1.PlayerScore = 0;
                    Player2.PlayerScore = 0;
                    Player1.PlayerMoves--;
                    Player2.PlayerMoves--;
                    // position_array[turn - 1] = 0;
                    turn -= 2;
                    ColumnFreeSpacesArr[l]++;
                    ColumnFreeSpacesArr[m]++;
                    break;
                }
                k++;
            }
        }*/
    }
}
void redo(int game_mode)
{
    if (position_array[turn] != 0 && checkFreeSpaces() <= colmns * rows)
    {
        if (game_mode == 2)
        {
            int i = rows - 1;
            int j = position_array[turn] - 1;
            while (i >= 0)
            {
                if (board[i][j] == ' ')
                {
                    if (player_turn_arr[turn] == 1)
                    {
                        board[i][j] = Player1Symbol;
                        Player1.PlayerMoves++;
                    }
                    else
                    {
                        board[i][j] = Player2Symbol;
                        Player2.PlayerMoves++;
                    }
                    turn++;
                    ColumnFreeSpacesArr[j]--;
                    break;
                }
                i--;
            }
        }
        /*else if (game_mode == 1)
        {
            int k = rows - 1;
            int l = position_array[turn] - 1;
            int m = position_array[turn + 1] - 1;
            while (k >= 0)
            {
                if (board[k][l] == ' ' && board[k][m] == ' ')
                {
                    board[k][l] = Player1Symbol;
                    Player1.PlayerMoves++;
                    board[k][m] = Player2Symbol;
                    Player2.PlayerMoves++;
                }
                turn += 2;
                ColumnFreeSpacesArr[l]--;
                ColumnFreeSpacesArr[m]--;
                break;
            }
            k--;
        }
    }*/
        Player1.PlayerScore = 0;
        Player2.PlayerScore = 0;
    }
}
