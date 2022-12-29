#include "SaveAndLoad.h"
#include "SaveAndLoad.h"
#include "GameLoop.c"
void file_save(int file_number,int r , int c , int position[r*c], int turn , int moves1 ,int moves2 ,int score1 ,int  score2 , char grid[r*c])
{ // file number from save menu
    if (file_number == 1)
    {
        FILE *p;
        p = fopen("SaveGame1.txt","wb");
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&position[i],sizeof(position[i]),1,p);
        }
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&grid[i],sizeof(grid[i]),1,p);
        }
        fwrite(&moves1,sizeof(moves1),1, p);
        fwrite(&moves2,sizeof(moves2),1, p);
        fwrite(&score1,sizeof(score1),1, p);
        fwrite(&score2,sizeof(score2),1, p);

        fwrite(&turn,sizeof(turn),1, p);

        fclose (p);
    }
    else if (file_number == 2)
    {
        FILE *p;
        p = fopen("SaveGame2.txt","wb");
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&position[i],sizeof(position[i]),1,p);
        }
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&grid[i],sizeof(grid[i]),1,p);
        }
        fwrite(&moves1,sizeof(moves1),1, p);
        fwrite(&moves2,sizeof(moves2),1, p);
        fwrite(&score1,sizeof(score1),1, p);
        fwrite(&score2,sizeof(score2),1, p);

        fwrite(&turn,sizeof(turn),1, p);

        fclose (p);
    }
    else if (file_number == 3)
    {
        FILE *p;
        p = fopen("SaveGame3.txt","wb");
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&position[i],sizeof(position[i]),1,p);
        }
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&grid[i],sizeof(grid[i]),1,p);
        }
        fwrite(&moves1,sizeof(moves1),1, p);
        fwrite(&moves2,sizeof(moves2),1, p);
        fwrite(&score1,sizeof(score1),1, p);
        fwrite(&score2,sizeof(score2),1, p);

        fwrite(&turn,sizeof(turn),1, p);

        fclose (p);
    }
}



void Load ()                     // Save File 1
{
    FILE *pr;
    pr = fopen("SaveGame1.txt","rb");
    for (int i=0 ; i<rows*colmns ; i++)
    {
            fread(&position_array[i],sizeof(position_array[i]),1,pr);
    }
    for (int i=0 ; i<rows*colmns ; i++)
    {
            fread(&board[i],sizeof(board[i]),1,pr);
    }
    fwrite(&Player1.PlayerMoves,sizeof(Player1.PlayerMoves),1, pr);
    fwrite(&Player2.PlayerMoves,sizeof(Player2.PlayerMoves),1, pr);
    fwrite(&Player1.PlayerScore,sizeof(Player1.PlayerScore),1, pr);
    fwrite(&Player2.PlayerScore,sizeof(Player2.PlayerScore),1, pr);

    fwrite(&turn,sizeof(turn),1, pr);

    fclose(pr);
}
