#include "LoadAndSave.h"

int var;
int info[6] = {0};
int ok;
void file_save(int file_number, int r, int c,  int turn, int moves1, int moves2, int score1, int score2, int t)
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