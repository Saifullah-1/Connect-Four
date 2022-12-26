#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "GameLoop.h"

int rows = 4;
int colmns = 4;
char board[/*rows=*/4][/*columns=*/4]; // read dimentions from xml file
int player_turn_arr[/*rows*columns+2*/ 4 * 4 + 2];
int turn = 0;
int ColumnFreeSpacesArr[/*columns*/ 4];

/*int search(char a[], char b[]){
    int count = -1,i=0;
    while (b[i]!='\0')
    {
        int j = 0;
        if (b[i]==a[j])
        {
            int k = 0;
            while (b[k]==a[j]&&a[j]!='\0')
            {
                k++;
                j++;
            }
            if (a[j]=='\0')
            {
                count = i;
            }
        }
        i++;
    }
    return (count);
}
void XML(void){
    char x, y[200]={'0'}, conf_start[]="<Configurations>", height_start[]="<Height>", width_start[]="<Width>", highscores_start="<Highscores>";
    char conf_end[]="</Configurations>" ,height_end[]="</Height>", width_end[]="</Width>", highscores_end="</Highscores>";
    FILE *file1 = fopen("parameters.xml", "r");
    int i =0;
    while ((x=fgetc(file1))!=EOF)
    {
        if (x!=' '&&x!='\n'&&x!='\t')
        {
            y[i] = x;
            i++;
        }
    }
    int start = search(conf_start, y);
    int end = search(conf_end, y);
    int size = end - start +1;
    char arr[size];
    for (int a = 0; a < size; a++)arr[a]=y[start+a];
    int start_w = search(conf_start, y);
    int end_w = search(conf_end, y);
    char col[3];
    col[0] = arr[start_w+7];
    col[1] = arr[start_w+8];
    col[2] = '\0';
    int w, HS;
    if (start_w!=-1&&end_w!=-1&&(end_w-start_w==8||end_w-start_w==9)&&atoi(col)>=4)
    {
        colmns = atoi(col);
    }else
    {
        colmns = 7;
    }
    int start_h=search(height_start,arr);
    int end_h=search(height_end,arr);
    char row[3];
    row[0] = arr[start_w+8];
    row[1] = arr[start_w+9];
    row[2] = '\0';
    if (start_h!=-1&&end_h!=-1&&(end_h-start_h==9||end_h-start_h==10)&&atoi(row)>=4)
    {
        rows = atoi(row);
    }else
    {
        rows = 9;
    }
    int start_hs=search(highscores_start,arr);
    int end_hs=search(highscores_end,arr);
    char score[3];
    score[0] = arr[start_hs+12];
    score[1] = arr[start_hs+13];
    score[2] = '\0';
    if (start_hs!=-1&&end_hs!=-1&&(end_hs-start_hs==13||end_h-start_h==14)&&atoi(score)>=1)
    {
        no_of_scores = atoi(score);
    }else
    {
        no_of_scores = 10;
    }
    FILE *file2 = fclose(file1);
}*/

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
    return 0;
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
    printf("%c\t%d", name, s);
    fclose(Pscores);
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
                Player1.PlayerMoves++;
                ColumnFreeSpacesArr[columnNumber - 1]--;
                turn++;
                break;
            }
            else
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
    yellow();
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
        gotoxy(23 + (colmns)*4, 4);
        printf("Computer Turn");
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
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        red();
        printf("Player1 Won With score %i!\n Please Enter Player1 Name : ", Player1.PlayerScore);
        gets(Player1.PlayerName);
        SaveTop(Player1.PlayerName, Player1.PlayerScore);
    }
    else if (Player1.PlayerScore < Player2.PlayerScore)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        LightBlue();
        printf("Player2 Won With score %i!\n Please Enter Player2 Name : ", Player2.PlayerScore);
        gets(Player2.PlayerName);
        SaveTop(Player2.PlayerName, Player2.PlayerScore);
    }
    else
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                            ");
        gotoxy(0, 8 + (rows - 1) * 2);
        reset();
        printf("Draw! Please Enter Player1 Name : ");
        scanf("%s", Player1.PlayerName);
        gets(Player1.PlayerName);
        printf("\nPlease Enter Player2 Name : ");
        gets(Player2.PlayerName);
        SaveTop(Player2.PlayerName, Player2.PlayerScore);
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
int inGameMenu(void)
{
    int choice;
    char userInput[100];
    while (1)
    {
        gotoxy(0, 8 + (rows - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (rows - 1) * 2);
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
int afterGame(void)
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
void undo(void)
{
}
void redo(void)
{
}
