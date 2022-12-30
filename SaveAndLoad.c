#include "SaveAndLoad.h"
#include "GameLoop.c"

int var;
int info[6]={0};
int ok;
void file_save(int file_number,int r , int c , int position[r*c], int turn , int moves1 ,int moves2 ,int score1 ,int  score2 , char grid[r][c] , int t)
{
    FILE *p;
    if (file_number == 1)
    {
        p = fopen("SaveGame1.bin","wb");
    }

    else if (file_number == 2)
    {
        p = fopen("SaveGame2.bin","wb");
    }

    else if (file_number == 3)
    {
        p = fopen("SaveGame3.bin","wb");
    }
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

void Load (int slot)                     // Save File 1
{
    FILE* p;

    if (slot ==1)
    {
    p=fopen ("SaveGame1.bin","rb");
    }

    else if (slot ==2)
    {
    p=fopen ("SaveGame2.bin","rb");
    }

    if (slot ==3)
    {
    p=fopen ("SaveGame3.bin","rb");
    }


    if(p == NULL)
        ok=0;
    else if(p != NULL){
    ok=1;
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
    }
    fclose(p);
}




int Scores[500];
char Names[500][100];

int ScoresMod[100];
char NamesMod[100][100];


void Top(char s[100] , int n)
{

    FILE*p;
    p = fopen("Top.bin","rb");

    int ind=0;
    int j=0;

    while (!feof(p))
    {
        if(fread(Names[j],sizeof(Names[j]),1,p) == 0)
            break;
        else
        {
        fread(&Scores[j],sizeof(Scores[j]),1,p);
        ind++;
        j++;
        }
    }
    fclose (p);

    var = ind;
}




void CheckRepeated()               // Ignoring Duplicate Names
{
    for (int i=0 ; i<var-1 ; i++)
    {
        for (int k=1+i ; k<var ; k++)
        {
            if (Names[i]!=" " & (strcasecmp(Names[i],Names[k])==0))
            {
                if (Scores[i]>=Scores[k])
                {
                    strcpy(Names[k]," ");
                    Scores[k] =-1;
                }
                else if (Scores[i]<Scores[k])
                {
                    strcpy(Names[i]," ");
                    Scores[i] =-1;
                }
            }
        }
    }
}

void Sort()                // Sorting Our File
{
    int sorted = 0;
    int num=0;
    int flag=0;

    for (int i=0 ; i<var ; i++)
    {
        if (Names[i]!=" " && Scores[i]!=-1)
        {
        ScoresMod[num] = Scores[i];
        strcpy(NamesMod[num],Names[i] );
        flag++;
        num++;
        }
    }



    while (!sorted)
    {
        sorted = 1;
        for (int k = 0 ; k < num-1 ; k++)
        {
           if (ScoresMod[k] < ScoresMod [k+1] )
           {
               int temp = ScoresMod[k];
               ScoresMod [k] = ScoresMod [k+1];
               ScoresMod [k+1] = temp;

               char ch[100];
               strcpy (ch,NamesMod[k]);
               strcpy (NamesMod[k],NamesMod[k+1]);
               strcpy (NamesMod[k+1],ch);
           }
        }
        num -= 1;
    }


    FILE* ptr;
    ptr = fopen ("Top.bin","wb");

    for (int i =0 ; i<flag ; i++)
    {
        fwrite(NamesMod[i] , sizeof(NamesMod[i]) , 1 , ptr);
        fwrite(&ScoresMod[i] , sizeof(ScoresMod[i]) , 1 , ptr);
    }

    fclose (ptr);

}

void callTopScores(int n)                  // Calling The Top N Scores With Their Players
{
    int x;
    char y[100];

    FILE* ptr;
    ptr = fopen ("Top.bin" , "rb");

    for (int i=0 ; i<n ; i++)
    {
       fread(y , sizeof(y) , 1 , ptr);
       fread(&x , sizeof(x) , 1 , ptr);
       printf ("\n[%d]- %s With Score %d\n",i+1,y,x);
    }

    fclose (ptr);
}
