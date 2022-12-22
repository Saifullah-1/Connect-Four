#ifndef GAME_LOOP /*Header Guard*/
#define GAME_LOOP
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "GameLoop.c"

void resetPlayerData(void);
void grid_design(void);
void playerData(void);
void scan_column_number (int column, int max, int min);
#endif