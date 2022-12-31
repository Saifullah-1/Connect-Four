#ifndef GAME_LOOP /*Header Guard*/
#define GAME_LOOP
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "GameLoop.c"

int searchInXML(char a[], char b[]);
void XML ();
void Time (int start , int end);
void CheckPlaces();
void resetPlayerTurnArr(int mode);
void resetColumnFreeSpacesArr(void);
void resetPlayerData(void);
void resetBoard(void);
void printBoard(void);
int checkFreeSpaces(void);
void playerMove(void);
void computerMove(void);
void checkScore(void);
void playerData(int game_mode);
void checkWinner(int game_mode);

#endif