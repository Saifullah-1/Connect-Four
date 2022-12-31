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
configuration conf = {.width = 9, .height = 7, .scores = 10};

char board[100][100]; // read dimentions from xml file
int position_array[100];
int player_turn_arr[100];
int turn = 0;
int ColumnFreeSpacesArr[100];


// FUNCTION TO CHECK IF WORD IS FOUND IN STRING OR NOT
int searchInXML(char a[], char b[])
{
    int counter = -1, i = 0;
    while (b[i] != '\0')
    {
        int j = 0;
        if (b[i] == a[j])
        {
            int k = i;
            while (b[k] == a[j] && a[j] != '\0')
            {
                k++;
                j++;
            }
            if (a[j] == '\0')
            {
                counter = i;
            }
        }
        i++;
    }
    return counter;
}
// FUNCTION TO READ FROM XML FILE
void XML()
{
    char y, x[200] = {'0'}, conf_1[] = "<Configurations>", width_1[] = "<Width>", height_1[] = "<Height>", highscores_1[] = "<Highscores>";
    char conf_2[] = "</Configurations>", width_2[] = "</Width>", height_2[] = "</Height>", highscores_2[] = "</Highscores>";
    int i = 0, start, end, start_w, end_w, start_h, end_h, start_hs, end_hs, len, a, size, HS, H, W;
    FILE *file = fopen("parameters.xml", "r");
    while ((y = fgetc(file)) != EOF)
    {
        if (y != ' ' && y != '\n' && y != '\t')
        { // IGNORING ANY SPACES OR TABS OR BREAKING LINE
            x[i] = y;
            i++;
            len++;
        }
    }
    start = searchInXML(conf_1, x); // CALLING OVERLAPPING FUNCTION
    end = searchInXML(conf_2, x);
    size = end - start + 1;
    if (start == -1 || end == -1)
    {
        printf("File Corrupted\n");
        printf("Wait Loading Default Values ......");
        W = 9;
        H = 7;
        HS = 10;
        conf.width = W;   // CHANGING THE GLOBAL VALUE FOR WIDTH
        conf.height = H;  // CHANGING THE GLOBAL VALUE FOR HEIGHT
        conf.scores = HS; // CHANGING THE GLOBAL VAUE FOR HIGH SCORE
        board[conf.height][conf.width];
        ColumnFreeSpacesArr[conf.width];
        position_array[conf.height * conf.width];
        player_turn_arr[conf.height * conf.width];
        Sleep(1000);
        fclose(file);
        return;
    }
    char array[size]; // ARRAY TO RED BETWEEN TWO CONFIGRATIONS TAGS
    for (a = 0; a < size; a++)
        array[a] = x[start + a]; // INTIALIZATION FOR NWE ARRAY
    start_w = searchInXML(width_1, array);
    end_w = searchInXML(width_2, array);
    char row[3]; // CHECKING OPENING AND CLOSING THE TAGS IN RIGHT WAY
    row[0] = array[start_w + 7];
    row[1] = array[start_w + 8];
    row[2] = '\0';
    if (start_w != -1 && end_w != -1 && (end_w - start_w == 8 || end_w - start_w == 9) && atoi(row) >= 4)
        W = atoi(row);
    else
    { // SET THE DEFULT IN THERE IS WRONG IN READING THE XML FILE
        printf("File Corrupted\n");
        printf("Wait Loading Default Values ......");
        W = 9;
        H = 7;
        HS = 10;
        Sleep(1000);
    }
    start_h = searchInXML(height_1, array); // CALLING THE OVERLAPPING FUNCTION
    end_h = searchInXML(height_2, array);
    char col[3]; // CHECK OPENING AND CLOSING THE TAGS IN WRIGHT WAY
    col[0] = array[start_h + 8];
    col[1] = array[start_h + 9];
    col[2] = '\0';
    if (start_h != -1 && end_h != -1 && (end_h - start_h == 9 || end_h - start_h == 10) && atoi(col) >= 4)
        H = atoi(col);
    else
    {
        printf("File Corrupted\n");
        printf("Wait Loading Default Values ......");
        W = 9;
        H = 7;
        HS = 10;
        Sleep(1000);
    }
    start_hs = searchInXML(highscores_1, array);
    end_hs = searchInXML(highscores_2, array); // CALLING OVER LAPPING FUNCTIONS
    char score[3];
    score[0] = array[start_hs + 12]; // PUTTING BETWEEN TAGS IN ARRAY FOR READING WITH ATOI
    score[1] = array[start_hs + 13];
    score[2] = '\0';
    if (start_hs != -1 && end_hs != -1 && (end_hs - start_hs == 13 || end_hs - start_hs == 14))
        HS = atoi(score);
    else
    {
        printf("File Corrupted\n");
        printf("Wait Loading Default Values ......");
        W = 9;
        H = 7;
        HS = 10;
        Sleep(2000);
    }

    conf.width = W;   // CHANGING THE GLOBAL VALUE FOR WIDTH
    conf.height = H;  // CHANGING THE GLOBAL VALUE FOR HEIGHT
    conf.scores = HS; // CHANGING THE GLOBAL VAUE FOR HIGH SCORE
    board[conf.height][conf.width];
    ColumnFreeSpacesArr[conf.width];
    position_array[conf.height * conf.width];
    player_turn_arr[conf.height * conf.width+2];
    fclose(file);
}
int var;
int info[6] = {0};
int ok;
void file_save(int file_number, int r, int c, /*int position[],*/ int turn, int moves1, int moves2, int score1, int score2, /*char grid[r][c],*/ int t)
{
    FILE *p;
    if (file_number == 1)
    {
        p = fopen("SaveGame1.bin", "wb");
    }

    else if (file_number == 2)
    {
        p = fopen("SaveGame2.bin", "wb");
    }

    else if (file_number == 3)
    {
        p = fopen("SaveGame3.bin", "wb");
    }
    for (int i = 0; i < r * c; i++)
    {
        fwrite(&position_array[i], sizeof(position_array[i]), 1, p);
    }
    fwrite(&moves1, sizeof(moves1), 1, p);
    fwrite(&moves2, sizeof(moves2), 1, p);
    fwrite(&score1, sizeof(score1), 1, p);
    fwrite(&score2, sizeof(score2), 1, p);
    fwrite(&turn, sizeof(turn), 1, p);
    fwrite(&t, sizeof(t), 1, p);

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            fwrite(&board[i][j], sizeof(board[i][j]), 1, p);
    }
    fclose(p);
}

void Load(int slot)
{
    FILE *p;

    if (slot == 1)
    {
        p = fopen("SaveGame1.bin", "rb");
    }

    else if (slot == 2)
    {
        p = fopen("SaveGame2.bin", "rb");
    }

    if (slot == 3)
    {
        p = fopen("SaveGame3.bin", "rb");
    }

    if (p == NULL)
        ok = 0;
    else if (p != NULL)
    {
        ok = 1;
        for (int i = 0; i < conf.height * conf.width; i++)
        {
            fread(&position_array[i], sizeof(position_array[i]), 1, p);
        }

        for (int i = 0; i < 6; i++)
        {
            fread(&info[i], sizeof(info[i]), 1, p);
        }

        for (int i = 0; i < conf.height; i++)
        {
            for (int j = 0; j < conf.width; j++)
                fread(&board[i][j], sizeof(board[i][j]), 1, p);
        }
    }
    fclose(p);
}

int Scores[500];
char Names[500][100];

int ScoresMod[100];
char NamesMod[100][100];

void Top(char s[100], int n)
{

    FILE *p;
    p = fopen("Top.bin", "rb");

    int ind = 0;
    int j = 0;

    while (!feof(p))
    {
        if (fread(Names[j], sizeof(Names[j]), 1, p) == 0)
            break;
        else
        {
            fread(&Scores[j], sizeof(Scores[j]), 1, p);
            ind++;
            j++;
        }
    }
    fclose(p);

    var = ind;
}

void CheckRepeated() // Ignoring Duplicate Names
{
    for (int i = 0; i < var - 1; i++)
    {
        for (int k = 1 + i; k < var; k++)
        {
            if (Names[i] != " " & (strcasecmp(Names[i], Names[k]) == 0))
            {
                if (Scores[i] >= Scores[k])
                {
                    strcpy(Names[k], " ");
                    Scores[k] = -1;
                }
                else if (Scores[i] < Scores[k])
                {
                    strcpy(Names[i], " ");
                    Scores[i] = -1;
                }
            }
        }
    }
}

void Sort() // Sorting Our File
{
    int sorted = 0;
    int num = 0;
    int flag = 0;

    for (int i = 0; i < var; i++)
    {
        if (Names[i] != " " && Scores[i] != -1)
        {
            ScoresMod[num] = Scores[i];
            strcpy(NamesMod[num], Names[i]);
            flag++;
            num++;
        }
    }

    while (!sorted)
    {
        sorted = 1;
        for (int k = 0; k < num - 1; k++)
        {
            if (ScoresMod[k] < ScoresMod[k + 1])
            {
                int temp = ScoresMod[k];
                ScoresMod[k] = ScoresMod[k + 1];
                ScoresMod[k + 1] = temp;

                char ch[100];
                strcpy(ch, NamesMod[k]);
                strcpy(NamesMod[k], NamesMod[k + 1]);
                strcpy(NamesMod[k + 1], ch);
            }
        }
        num -= 1;
    }

    FILE *ptr;
    ptr = fopen("Top.bin", "wb");

    for (int i = 0; i < flag; i++)
    {
        fwrite(NamesMod[i], sizeof(NamesMod[i]), 1, ptr);
        fwrite(&ScoresMod[i], sizeof(ScoresMod[i]), 1, ptr);
    }

    fclose(ptr);
}

void callTopScores(int n) // Calling The Top N Scores With Their Players
{
    int x;
    char y[100];

    FILE *ptr;
    ptr = fopen("Top.bin", "rb");

    for (int i = 0; i < n; i++)
    {
        fread(y, sizeof(y), 1, ptr);
        fread(&x, sizeof(x), 1, ptr);
        printf("\n[%d]- %s With Score %d\n", i + 1, y, x);
    }

    fclose(ptr);
}
int hours, minutes, seconds;

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

void CheckPlaces()
{
    for (int i = 0; i < conf.width; i++)
    {
        for (int j = 0; j < conf.height; j++)
        {
            if (board[j][i] == ' ')
            {
                ColumnFreeSpacesArr[i] += 1;
            }
        }
    }
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
    for (int i = 0; i < conf.height * conf.width; i += 2)
    {
        player_turn_arr[i] = 1;
        player_turn_arr[i + 1] = mode;
    }
}
void resetColumnFreeSpacesArr(void) // array for free spaces in each column
{
    for (int i = 0; i < conf.width; i++)
    {
        ColumnFreeSpacesArr[i] = conf.height;
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
    for (int i = 0; i < conf.height; i++)
    {
        for (int j = 0; j < conf.width; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard(void) // board
{
    gotoxy(0, 3);
    yellow();
    for (int i = 1; i <= conf.width; i++)
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
    for (int i = 0; i < conf.height; i++)
    {
        for (int k = 0; k < conf.width; k++)
        {
            printf("|---");
        }
        printf("|");
        printf("\n");
        for (int j = 0; j < conf.width; j++)
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
    for (int k = 0; k < conf.width; k++)
    {
        printf("|---");
    }
    printf("|");
    printf("\n");
}
int checkFreeSpaces(void) // free spaces in board  if free spaces == 0 game ends
{
    int freeSpaces = conf.height * conf.width;
    for (int i = 0; i < conf.height; i++)
    {
        for (int j = 0; j < conf.width; j++)
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
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("                                                                                                      ");
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("Please Enter A Non Full Column Number from 1 to %i : ", conf.width);
        scanf("%d", &columnNumber);
        fflush(stdin);
        if (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > conf.width)
        {
            gotoxy(0, 8 + (conf.height - 1) * 2);
            printf("                                                                                                      ");
        }
        else
        {
            position_array[turn] = columnNumber;
            for (int i = turn + 1; i < conf.height * conf.width + 2; i++)
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
    } while (ColumnFreeSpacesArr[columnNumber - 1] == 0 || columnNumber < 1 || columnNumber > conf.width);
}

// VS computer
void computerMove(void)
{
    int found = 0;
    // first try to make a progress
    //  [1] try to make 4 vertical adjacent disks
    for (int j = 0; j < conf.width; j++)
    {
        for (int i = conf.height - 1; i >= 3; i--)
        {
            if (board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] && board[i][j] == Player2Symbol)
            {
                if (board[i - 3][j] == ' ')
                {
                    board[i - 3][j] = Player2Symbol;
                    position_array[turn] = j + 1;
                    ColumnFreeSpacesArr[j]--;
                    Player2.PlayerMoves++;
                    turn++;
                    found = 1;
                    break;
                }
            }
        }
        if (found == 1)
        {
            break;
        }
    }
    // [2] if first not found try to make 4 horizontal adjacent disks
    if (found == 0)
    {
        for (int i = conf.height - 1; i >= 0; i--)
        {
            for (int j = 0; j <= conf.width - 4; j++)
            {
                if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j] == Player2Symbol)
                {
                    if (i == conf.height - 1)
                    {
                        if (board[i][j + 3] == ' ')
                        {
                            board[i][j + 3] = Player2Symbol;
                            position_array[turn] = j + 4;
                            ColumnFreeSpacesArr[j + 3]--;
                            Player2.PlayerMoves++;
                            turn++;
                            found = 1;
                            break;
                        }
                    }
                    else
                    {
                        if (board[i][j + 3] == ' ' && board[i + 1][j + 3] != ' ')
                        {
                            board[i][j + 3] = Player2Symbol;
                            position_array[turn] = j + 4;
                            ColumnFreeSpacesArr[j + 3]--;
                            Player2.PlayerMoves++;
                            turn++;
                            found = 1;
                            break;
                        }
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    //[3] if first and second not found try to make 4 diagonal adjacent disks
    if (found == 0)
    {
        // first diagonal case
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = 0; j < conf.width - 3; j++)
            {
                if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i][j] == Player2Symbol)
                {
                    if (board[i - 3][j + 3] == ' ' && board[i - 2][j + 3] != ' ')
                    {
                        board[i - 3][j + 3] = Player2Symbol;
                        position_array[turn] = j + 4;
                        ColumnFreeSpacesArr[j + 3]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    if (found == 0)
    {
        // second diagonal case
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = conf.width - 1; j >= 3; j--)
            {
                if (board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2] && board[i][j] == Player2Symbol)
                {
                    if (board[i - 3][j - 3] == ' ' && board[i - 2][j - 3] != ' ')
                    {
                        board[i - 3][j - 3] = Player2Symbol;
                        position_array[turn] = j - 2;
                        ColumnFreeSpacesArr[j - 3]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    // second if all above conditions not found try to prevent the player making progress
    //[1]try to prevent the player making 4 vertical adjacent disks
    if (found == 0)
    {
        for (int j = 0; j < conf.width; j++)
        {
            for (int i = conf.height - 1; i >= 3; i--)
            {
                if (board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] && board[i][j] == Player1Symbol)
                {
                    if (board[i - 3][j] == ' ')
                    {
                        board[i - 3][j] = Player2Symbol;
                        position_array[turn] = j + 1;
                        ColumnFreeSpacesArr[j]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    //[2]try to prevent the player making 4 horizontal adjacent disks
    if (found == 0)
    {
        for (int i = conf.height - 1; i >= 0; i--)
        {
            for (int j = 0; j <= conf.width - 4; j++)
            {
                if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j] == Player1Symbol)
                {
                    if (i == conf.height - 1)
                    {
                        if (board[i][j + 3] == ' ')
                        {
                            board[i][j + 3] = Player2Symbol;
                            position_array[turn] = j + 4;
                            ColumnFreeSpacesArr[j + 3]--;
                            Player2.PlayerMoves++;
                            turn++;
                            found = 1;
                            break;
                        }
                    }
                    else
                    {
                        if (board[i][j + 3] == ' ' && board[i + 1][j + 3] != ' ')
                        {
                            board[i][j + 3] = Player2Symbol;
                            position_array[turn] = j + 4;
                            ColumnFreeSpacesArr[j + 3]--;
                            Player2.PlayerMoves++;
                            turn++;
                            found = 1;
                            break;
                        }
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }

    //[3]try to prevent the player making 4 diagonal adjacent disks
    if (found == 0)
    {
        // first diagonal case
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = 0; j < conf.width - 3; j++)
            {
                if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i][j] == Player1Symbol)
                {
                    if (board[i - 3][j + 3] == ' ' && board[i - 2][j + 3] != ' ')
                    {
                        board[i - 3][j + 3] = Player2Symbol;
                        position_array[turn] = j + 4;
                        ColumnFreeSpacesArr[j + 3]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    if (found == 0)
    {
        // second diagonal case
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = conf.width - 1; j >= 3; j--)
            {
                if (board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2] && board[i][j] == Player1Symbol)
                {
                    if (board[i - 3][j - 3] == ' ' && board[i - 2][j - 3] != ' ')
                    {
                        board[i - 3][j - 3] = Player2Symbol;
                        position_array[turn] = j - 2;
                        ColumnFreeSpacesArr[j - 3]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    // third try to build 3 adjacent disks
    //[1]try to make 3 vertical adjacent disks
    if (found == 0)
    {
        for (int j = 0; j < conf.width; j++)
        {
            for (int i = conf.height - 1; i >= 3; i--)
            {
                if (board[i][j] == board[i - 1][j] && board[i][j] == Player2Symbol)
                {
                    if (board[i - 2][j] == ' ')
                    {
                        board[i - 2][j] = Player2Symbol;
                        position_array[turn] = j + 1;
                        ColumnFreeSpacesArr[j]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    //[2]try to make 3 horizontol adjacent disks
    if (found == 0)
    {
        for (int i = conf.height - 1; i >= 0; i--)
        {
            for (int j = 0; j <= conf.width - 4; j++)
            {
                if (board[i][j] == board[i][j + 1] && board[i][j] == Player2Symbol)
                {
                    if (i == conf.height - 1)
                    {
                        if (board[i][j + 2] == ' ')
                        {
                            board[i][j + 2] = Player2Symbol;
                            position_array[turn] = j + 3;
                            ColumnFreeSpacesArr[j + 2]--;
                            Player2.PlayerMoves++;
                            turn++;
                            found = 1;
                            break;
                        }
                    }
                    else
                    {
                        if (board[i][j + 2] == ' ' && board[i + 1][j + 2] != ' ')
                        {
                            board[i][j + 2] = Player2Symbol;
                            position_array[turn] = j + 3;
                            ColumnFreeSpacesArr[j + 2]--;
                            Player2.PlayerMoves++;
                            turn++;
                            found = 1;
                            break;
                        }
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    //[3]try to make 3 diagonal adjacent disks
    if (found == 0) // first case
    {
        // first diagonal case making 3 adjacent
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = 0; j < conf.width - 3; j++)
            {
                if (board[i][j] == board[i - 1][j + 1] && board[i][j] == Player2Symbol)
                {
                    if (board[i - 2][j + 2] == ' ' && board[i - 1][j + 2] != ' ')
                    {
                        board[i - 2][j + 2] = Player2Symbol;
                        position_array[turn] = j + 3;
                        ColumnFreeSpacesArr[j + 2]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    if (found == 0) // first case
    {
        // second diagonal case making 3 adjacent
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = conf.width - 1; j >= 3; j--)
            {
                if (board[i][j] == board[i - 1][j - 1] && board[i][j] == Player2Symbol)
                {
                    if (board[i - 2][j - 2] == ' ' && board[i - 1][j - 2] != ' ')
                    {
                        board[i - 2][j - 2] = Player2Symbol;
                        position_array[turn] = j - 1;
                        ColumnFreeSpacesArr[j - 2]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    // third try to make 2 adjacent disks
    //[1] try to make 2 vertical adjacent disks
    if (found == 0)
    {
        for (int j = 0; j < conf.width; j++)
        {
            for (int i = conf.height - 1; i >= 3; i--)
            {
                if (board[i][j] == Player2Symbol && board[i - 1][j] == ' ')
                {
                    board[i - 1][j] = Player2Symbol;
                    position_array[turn] = j + 1;
                    ColumnFreeSpacesArr[j]--;
                    Player2.PlayerMoves++;
                    turn++;
                    found = 1;
                    break;
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    if (found == 0)
    {
        // [2]try to make 2 horizontol adjacent disks
        for (int i = conf.height - 1; i >= 0; i--)
        {
            for (int j = 0; j <= conf.width - 4; j++)
            {
                if (i == conf.height - 1)
                {
                    if (board[i][j] == Player2Symbol && board[i][j + 1] == ' ')
                    {
                        board[i][j + 1] = Player2Symbol;
                        position_array[turn] = j + 2;
                        ColumnFreeSpacesArr[j + 1]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
                else
                {
                    if (board[i][j] == Player2Symbol && board[i][j + 1] == ' ' && board[i + 1][j + 1] != ' ')
                    {
                        board[i][j + 1] = Player2Symbol;
                        position_array[turn] = j + 2;
                        ColumnFreeSpacesArr[j + 1]--;
                        Player2.PlayerMoves++;
                        turn++;
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    // [3]try to make 2 diagonal adjacent disks
    if (found == 0)
    {
        // first diagonal case making 2 adjacent
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = 0; j < conf.width - 3; j++)
            {
                if (board[i][j] == Player2Symbol && board[i - 1][j + 1] == ' ' && board[i][j + 1] != ' ')
                {
                    board[i - 1][j + 1] = Player2Symbol;
                    position_array[turn] = j + 2;
                    ColumnFreeSpacesArr[j + 1]--;
                    Player2.PlayerMoves++;
                    turn++;
                    found = 1;
                    break;
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    if (found == 0)
    {
        // second diagonal case making 2 adjacent
        for (int i = conf.height - 1; i >= 3; i--)
        {
            for (int j = conf.width - 1; j >= 3; j--)
            {
                if (board[i][j] == Player2Symbol && board[i - 1][j - 1] == ' ' && board[i][j - 1] != ' ')
                {
                    board[i - 1][j - 1] = Player2Symbol;
                    position_array[turn] = j;
                    ColumnFreeSpacesArr[j - 1]--;
                    Player2.PlayerMoves++;
                    turn++;
                    found = 1;
                    break;
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
    // if all the above not found play random
    if (found == 0)
    {
        for (int j = 0; j < conf.width; j++)
        {
            for (int i = conf.height - 1; i >= 0; i--)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = Player2Symbol;
                    position_array[turn] = j + 1;
                    ColumnFreeSpacesArr[j]--;
                    Player2.PlayerMoves++;
                    turn++;
                    found = 1;
                    break;
                }
            }
            if (found == 1)
            {
                break;
            }
        }
    }
}

void checkScore(void)
{
    // HORIZONTAL
    for (int i = 0; i < conf.height; i++)
    {
        for (int j = 0; j < conf.width - 3; j++)
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
    for (int j = 0; j < conf.width; j++)
    {
        for (int i = 0; i < conf.height - 3; i++)
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
    for (int i = 0; i < conf.height - 3; i++)
    {
        for (int j = 0; j < conf.width - 3; j++)
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
    for (int i = 0; i < conf.height - 3; i++)
    {
        for (int j = 3; j <= conf.width - 1; j++)
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
FILE *p;
void playerData(int game_mode) // game_mode = 1 in Vs computer mode and = 2 in Vs human mode
{
    
    if (turn < conf.height * conf.width)
    {
        if (player_turn_arr[turn] == 1)
        {
            gotoxy(23 + (conf.width) * 4, 4);
            red();
            printf("Player %i Turn", player_turn_arr[turn]);
        }
        else if (player_turn_arr[turn] == 2)
        {
            gotoxy(23 + (conf.width) * 4, 4);
            LightBlue();
            printf("Player %i Turn", player_turn_arr[turn]);
        }
        else if (player_turn_arr[turn] == 3)
        {
            yellow();
            gotoxy(23 + (conf.width) * 4, 4);
            printf("Computer Turn");
        }
    }
    else
    {
        gotoxy(23 + (conf.width) * 4, 4);
        printf("                                         ");
        gotoxy(23 + (conf.width) * 4, 4);
        reset();
        printf("Game Over!");
    }
    gotoxy(23 + (conf.width) * 4, 6);
    red();
    printf("Number of moves of Player1 : %02i", Player1.PlayerMoves);
    gotoxy(23 + (conf.width) * 4, 7);
    LightBlue();
    if (game_mode == 1)
    {
        printf("Number of moves of Computer : %02i", Player2.PlayerMoves);
    }
    else
    {
        printf("Number of moves of Player2 : %02i", Player2.PlayerMoves);
    }
    gotoxy(23 + (conf.width) * 4, 8);
    red();
    printf("Player1 score: %i", Player1.PlayerScore);
    gotoxy(23 + (conf.width) * 4, 9);
    LightBlue();
    if (game_mode == 1)
    {
        printf("Computer score: %i", Player2.PlayerScore);
    }
    else
    {
        printf("Player2 score: %i", Player2.PlayerScore);
    }

    gotoxy(23 + (conf.width) * 4, 10);
    yellow();
    printf("Time passed: %02i:%02i:%02i", hours, minutes, seconds); // time function
}

void checkWinner(int game_mode)
{
    if (Player1.PlayerScore > Player2.PlayerScore)
    {
        if (game_mode == 2)
        {
            red();
            while (1)
            {
                gotoxy(0, 8 + (conf.height - 1) * 2);
                printf("                                                                                                                            ");
                gotoxy(0, 8 + (conf.height - 1) * 2);
                printf("Player1 Won With score %i!\n Please Enter Player1 Name : ", Player1.PlayerScore);
                gets(Player1.PlayerName);
                break;
            }
            
            p = fopen("Top.bin", "ab");
            fwrite(Player1.PlayerName, sizeof(Player1.PlayerName), 1, p);
            fwrite(&Player1.PlayerScore, sizeof(Player1.PlayerScore), 1, p);
            fclose(p);
            Top(Player1.PlayerName, Player1.PlayerScore);
            CheckRepeated();
            Sort();
        }
        else if (game_mode == 1)
        {
            red();
            while (1)
            {
                gotoxy(0, 8 + (conf.height - 1) * 2);
                printf("                                                                                                                            ");
                gotoxy(0, 8 + (conf.height - 1) * 2);
                gets(Player1.PlayerName);
                break;
            }
            
            p = fopen("Top.bin", "ab");
            fwrite(Player1.PlayerName, sizeof(Player1.PlayerName), 1, p);
            fwrite(&Player1.PlayerScore, sizeof(Player1.PlayerScore), 1, p);
            fclose(p);
            Top(Player1.PlayerName, Player1.PlayerScore);
            CheckRepeated();
            Sort();
        }
    }
    else if (Player1.PlayerScore < Player2.PlayerScore)
    {
        if (game_mode == 2)
        {
            LightBlue();
            gotoxy(0, 8 + (conf.height - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 8 + (conf.height - 1) * 2);
            while (1)
            {
                printf("Player2 Won With score %i!\n Please Enter Player2 Name : ", Player2.PlayerScore);
                gets(Player2.PlayerName);
                break;
            }
            
            p = fopen("Top.bin", "ab");
            fwrite(Player2.PlayerName, sizeof(Player2.PlayerName), 1, p);
            fwrite(&Player2.PlayerScore, sizeof(Player2.PlayerScore), 1, p);
            fclose(p);
            Top(Player2.PlayerName, Player2.PlayerScore);
            CheckRepeated();
            Sort();
        }
        else if (game_mode == 1)
        {
            LightBlue();
            gotoxy(0, 8 + (conf.height - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 8 + (conf.height - 1) * 2);
            while (1)
            {
                printf("YOU LOSE With score %i!\n Please Enter YOUR Name : ", Player1.PlayerScore);
                gets(Player1.PlayerName);
                break;
            }
            
            p = fopen("Top.bin", "ab");
            fwrite(Player1.PlayerName, sizeof(Player1.PlayerName), 1, p);
            fwrite(&Player1.PlayerScore, sizeof(Player1.PlayerScore), 1, p);
            fclose(p);
            Top(Player1.PlayerName, Player1.PlayerScore);
            CheckRepeated();
            Sort();
        }
    }
    else if (Player1.PlayerScore == Player2.PlayerScore)
    {
        if (game_mode == 2)
        {
            gotoxy(0, 8 + (conf.height - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 8 + (conf.height - 1) * 2);
            reset();
            printf("Draw!\n");
            red();
            while (1)
            {
                gotoxy(0, 9 + (conf.height - 1) * 2);
                printf("                                                                                                                            ");
                gotoxy(0, 9 + (conf.height - 1) * 2);
                printf("Please Enter Player1 Name : ");
                gets(Player1.PlayerName);

                break;
            }
            
            p = fopen("Top.bin", "ab");
            fwrite(Player1.PlayerName, sizeof(Player1.PlayerName), 1, p);
            fwrite(&Player1.PlayerScore, sizeof(Player1.PlayerScore), 1, p);
            fclose(p);
            Top(Player1.PlayerName, Player1.PlayerScore);
            CheckRepeated();
            Sort();
            LightBlue();
            while (1)
            {
                gotoxy(0, 10 + (conf.height - 1) * 2);
                printf("                                                                                                                            ");
                gotoxy(0, 10 + (conf.height - 1) * 2);
                printf("Please Enter Player2 Name : ");
                gets(Player2.PlayerName);

                break;
            }
            p = fopen("Top.bin", "ab");
            fwrite(Player2.PlayerName, sizeof(Player2.PlayerName), 1, p);
            fwrite(&Player2.PlayerScore, sizeof(Player2.PlayerScore), 1, p);
            fclose(p);
            Top(Player2.PlayerName, Player2.PlayerScore);
            CheckRepeated();
            Sort();
        }
        else if (game_mode == 1)
        {
            gotoxy(0, 8 + (conf.height - 1) * 2);
            printf("                                                                                                                            ");
            gotoxy(0, 8 + (conf.height - 1) * 2);
            reset();
            printf("DRAW %i:%i!\n", Player1.PlayerScore, Player2.PlayerScore);
            red();
            while (1)
            {
                gotoxy(0, 9 + (conf.height - 1) * 2);
                printf("                                                                                                                            ");
                gotoxy(0, 9 + (conf.height - 1) * 2);
                printf("Please Enter Player1 Name : ");
                gets(Player1.PlayerName);

                break;
            }
            FILE *p;
            p = fopen("Top.bin", "ab");
            fwrite(Player1.PlayerName, sizeof(Player1.PlayerName), 1, p);
            fwrite(&Player1.PlayerScore, sizeof(Player1.PlayerScore), 1, p);
            fclose(p);
            Top(Player1.PlayerName, Player1.PlayerScore);
            CheckRepeated();
            Sort();
        }
    }
}

void startGame(void)
{
    char userInput[100];
    while (1)
    {
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("Please Enter [1]T0 Start Game >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 == 1)
        {
            gotoxy(0, 8 + (conf.height - 1) * 2);
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
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (conf.height - 1) * 2);
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
            gotoxy(0, 8 + (conf.height - 1) * 2);
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
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 9 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 10 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("Please Enter The File You Will Save In  [1]File 1....[2]File 2....[3]File 3 >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 >= 1 && x - 48 <= 3)
        {
            gotoxy(0, 8 + (conf.height - 1) * 2);
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
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 9 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 10 + (conf.height - 1) * 2);
        printf("                                                                                                                                          ");
        gotoxy(0, 8 + (conf.height - 1) * 2);
        printf("Please Enter [1]Main Menu....[2]Exit >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 >= 1 && x - 48 <= 2)
        {
            gotoxy(0, 8 + (conf.height - 1) * 2);
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
    for (int i = 0; i < conf.width * conf.height; i++)
    {
        position_array[i] = 0;
    }
}
void undo(int game_mode)
{
    if (checkFreeSpaces() < conf.height * conf.width)
    {
        if (game_mode == 2) // vsHuman mode
        {
            int j = position_array[turn - 1] - 1;
            int i = 0;
            while (i < conf.height)
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
                    turn--;
                    ColumnFreeSpacesArr[j]++;
                    break;
                }
                i++;
            }
        }
        else if (game_mode == 1 && turn >= 2) // vsComputer mode
        {
            int l = position_array[turn - 1] - 1;
            int m = position_array[turn - 2] - 1;
            for (int i = 0; i < conf.height; i++)
            {
                if (board[i][m] == Player1Symbol)
                {
                    board[i][m] = ' ';
                    ColumnFreeSpacesArr[m]++;
                    Player1.PlayerMoves--;
                    Player1.PlayerScore = 0;
                    break;
                }
            }
            for (int i = 0; i < conf.height; i++)
            {
                if (board[i][l] == Player2Symbol)
                {
                    board[i][l] = ' ';
                    ColumnFreeSpacesArr[l]++;
                    Player2.PlayerMoves--;
                    Player2.PlayerScore = 0;
                    break;
                }
            }
            turn -= 2;
        }
    }
}

void redo(int game_mode)
{
    if (position_array[turn] != 0 && checkFreeSpaces() <= conf.height * conf.width)
    {
        if (game_mode == 2)
        {
            int i = conf.height - 1;
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
        else if (game_mode == 1)
        {
            int l = position_array[turn] - 1;
            int m = position_array[turn + 1] - 1;
            for (int i = conf.height - 1; i >= 0; i--)
            {
                if (board[i][l] == ' ')
                {
                    board[i][l] = Player1Symbol;
                    Player1.PlayerMoves++;
                    ColumnFreeSpacesArr[l]--;
                    break;
                }
            }
            for (int i = conf.height - 1; i >= 0; i--)
            {
                if (board[i][m] == ' ')
                {
                    board[i][m] = Player2Symbol;
                    Player2.PlayerMoves++;
                    ColumnFreeSpacesArr[m]--;
                    break;
                }
            }
            turn += 2;
        }
    }
    Player1.PlayerScore = 0;
    Player2.PlayerScore = 0;
}
