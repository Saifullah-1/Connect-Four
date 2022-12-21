#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include ""

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
    player1.color = blue();                   // Add The Header
    player2.color = red();                     // Add The Header
    
    player1.score = 0; , player1.NumOfMoves =0;                 
    player2.score = 0  , player2.NumOfMoves =0;              
    
    printf("Player 1 Name : ");
    scanf ("%s",player1.name);
    system("cls");

    printf("Player 2 Name : ");
    scanf ("%s",player2.name);
    system("cls");
    
    int start = clock();
    fun();                           //Clock Only Works With Functions , Loops X   ,,, The GameLoop Function
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
    
    printf("Player X Won , Great Job , And Now Please Enter Your Name : ");
    gets(playerX);
    printf("\nYour Highest Score Is &d",playerX.score);
    
    
    return 0;
}

