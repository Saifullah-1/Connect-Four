#ifndef LOAD_SAVE
#define LOAD_SAVE
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "LoadAndSave.c"
#include "GameLoop.h"
void file_save(int file_number, int r, int c,  int turn, int moves1, int moves2, int score1, int score2, int t);
void Load(int slot);
void Top(char s[100], int n);
void CheckRepeated();
void Sort();
void callTopScores(int n);
void CheckPlaces();
void resetUndoArray(void);
void undo(int game_mode);
void redo(int game_mode);

#endif