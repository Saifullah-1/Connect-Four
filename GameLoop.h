#ifndef GAME_LOOP /*Header Guard*/
#define GAME_LOOP
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "GameLoop.c"

void SaveTop(char s[],int n);
void Time (int start , int end);
void Instant_Save(int i , int j);
void TopScores(char name[] , int s);
void resetPlayerTurnArr(void);
void resetColumnFreeSpacesArr(void);
void resetPlayerData(void);
void resetBoard(void);
void printBoard(void);
int checkFreeSpaces(void);
void playerMove(void);
void computerMove(void);
void checkScore(void);
void playerData(void);
void checkWinner(void);
void startGame(void);
int inGameMenu(void);

#endif
