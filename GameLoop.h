#ifndef GAME_LOOP /*Header Guard*/
#define GAME_LOOP
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "GameLoop.c"

void resetPlayerTurnArr(void);
void resetColumnFreeSpacesArr(void);
void resetPlayerData(void);
void resetBoard(void);
void printBoard(void);
int checkFreeSpaces(void);
void checkColumnFreeSpaces(int column_index);
void playerMove(void);
void computerMove(void);
void checkScore(void);
void playerData(void);
#endif
