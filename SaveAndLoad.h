#ifndef Save_Load /*Header Guards*/
#define Save_Load
#include "SaveAndLoad.c"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
void file_save(int file_number,int r , int c , int position[r*c], int turn , int moves1 ,int moves2 ,int score1 ,int  score2 , char grid[r*c]);
#endif
void Load () ;
