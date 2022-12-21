#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

struct {
    char name[500];
    char color[500];
    int score;
    int NumOfMoves;
}player1 , player2 ;

void fun()
{

}

int main()
{
    printf("Player 1 Name : ");
    scanf ("%s",player1.name);
    system("cls");

    printf("Player 1 color : ");
    scanf ("%s",player1.color);
    system("cls");

    printf("Player 2 Name : ");
    scanf ("%s",player2.name);
    system("cls");

    printf("Player 2 color : ");
    scanf ("%s",player2.color);
    system("cls");

    int start = clock();
    fun();                           //Clock Only Works With Functions , Loops X
    int end = clock();
    int seconds = (end - start)/CLOCKS_PER_SEC;
    int minutes=0 , hours=0 ;
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
    printf("The Game Took \n%d HH : %d MM : %d SS \n",hours ,minutes,seconds);
    return 0;
}

