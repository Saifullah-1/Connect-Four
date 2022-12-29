#include "SaveAndLoad.h"
#include "SaveAndLoad.h"
#include "GameLoop.c"


int info[6]={0};

void file_save(int file_number,int r , int c , int position[r*c], int turn , int moves1 ,int moves2 ,int score1 ,int  score2 , char grid[r][c] , int t)
{
    if (file_number == 1)
    {
        FILE *p;
        p = fopen("SaveGame1.txt","wb");
        for (int i=0 ; i<r*c ; i++)
        {
                fwrite(&position[i],sizeof(position[i]),1,p);
        }
        fwrite(&moves1,sizeof(moves1),1,p);
        fwrite(&moves2,sizeof(moves2),1,p);
        fwrite(&score1,sizeof(score1),1,p);
        fwrite(&score2,sizeof(score2),1,p);
        fwrite(&turn,sizeof(turn),1,p);
        fwrite(&t,sizeof(t),1,p);

        for (int i=0 ; i<r ; i++)
        {
            for (int j=0 ; j<c ; j++)
                fwrite(&grid[i][j],sizeof(grid[i][j]),1,p);
        }
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
        fwrite(&moves1,sizeof(moves1),1,p);
        fwrite(&moves2,sizeof(moves2),1,p);
        fwrite(&score1,sizeof(score1),1,p);
        fwrite(&score2,sizeof(score2),1,p);
        fwrite(&turn,sizeof(turn),1,p);
        fwrite(&t,sizeof(t),1,p);

        for (int i=0 ; i<r ; i++)
        {
            for (int j=0 ; j<c ; j++)
                fwrite(&grid[i][j],sizeof(grid[i][j]),1,p);
        }
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
        fwrite(&moves1,sizeof(moves1),1,p);
        fwrite(&moves2,sizeof(moves2),1,p);
        fwrite(&score1,sizeof(score1),1,p);
        fwrite(&score2,sizeof(score2),1,p);
        fwrite(&turn,sizeof(turn),1,p);
        fwrite(&t,sizeof(t),1,p);

        for (int i=0 ; i<r ; i++)
        {
            for (int j=0 ; j<c ; j++)
                fwrite(&grid[i][j],sizeof(grid[i][j]),1,p);
        }
        fclose (p);
    }
}

void Load (int slot)                     // Save File 1
{
    if (slot ==1)
    {
    FILE* p;
    p=fopen ("SaveGame1.txt","rb");
    for (int i =0 ; i<rows*colmns ; i++)
    {
        fread(&position_array[i],sizeof(position_array[i]),1,p);
    }

    for (int i =0 ; i<6 ; i++)
    {
        fread (&info[i],sizeof(info[i]),1,p);
    }

    for (int i=0 ; i<rows ; i++)
        {
            for (int j=0 ; j<colmns ; j++)
                fread(&board[i][j],sizeof(board[i][j]),1,p);
        }
    fclose(p);
    }


    else if (slot ==2)
    {
    FILE* p;
    p=fopen ("SaveGame2.txt","rb");
    for (int i =0 ; i<rows*colmns ; i++)
    {
        fread(&position_array[i],sizeof(position_array[i]),1,p);
    }

    for (int i =0 ; i<6 ; i++)
    {
        fread (&info[i],sizeof(info[i]),1,p);
    }

    for (int i=0 ; i<rows ; i++)
        {
            for (int j=0 ; j<colmns ; j++)
                fread(&board[i][j],sizeof(board[i][j]),1,p);
        }
    fclose(p);
    }


    if (slot ==3)
    {
    FILE* p;
    p=fopen ("SaveGame3.txt","rb");
    for (int i =0 ; i<rows*colmns ; i++)
    {
        fread(&position_array[i],sizeof(position_array[i]),1,p);
    }

    for (int i =0 ; i<6 ; i++)
    {
        fread (&info[i],sizeof(info[i]),1,p);
    }

    for (int i=0 ; i<rows ; i++)
        {
            for (int j=0 ; j<colmns ; j++)
                fread(&board[i][j],sizeof(board[i][j]),1,p);
        }
    fclose(p);
    }
}



/*
void Load ()                     // Save File 1
{
    FILE *pr;
    pr = fopen("SaveGame1.txt","r");
        for (int i=0 ; i<rows*colmns ; i++)
        {
                fscanf(pr,"%d",&position_array[i]);
        }
        for (int i=0 ; i<rows ; i++)
        {
            for (int j=0 ; j<colmns ; j++)
                fscanf(pr,"%c",&board[i][j]);
        }
        for (int i =0 ; i<5 ; i++)
        {
            fscanf(pr,"%d",info+1);
        }

        //fprintf(p,"%d",t);

        fclose (pr);
}
*/







/*
int info[6]={0};

void file_save(int file_number,int r , int c , int position[r*c], int turn , int moves1 ,int moves2 ,int score1 ,int  score2 , char grid[r*c] , int t)
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
        fwrite(&t,sizeof(t),1, p);

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
        fwrite(&t,sizeof(t),1, p);

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
        fwrite(&t,sizeof(t),1, p);

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

    for (int i=0 ; i<6 ; i++)
    {
            fread(&info[i],sizeof(info[i]),1,pr);
    }

    fclose(pr);
}
*/
