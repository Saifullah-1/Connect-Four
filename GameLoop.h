#ifndef GAME_LOOP /*Header Guard*/
#define GAME_LOOP
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "GameLoop.c"

void file_save(int file_number,int r , int c , int turn , int moves1 ,int moves2 ,int score1 ,int  score2 /*, char grid[r][c]*/ , int t);
void Load(int) ;
void Top(char s[100] , int n);
void CheckRepeated();
void Sort();
void callTopScores(int n);
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
void startGame(void);
int inGameMenu(void);
int saveMenu(void);
int afterGame(void);
void resetUndoArray(void);
void undo(int game_mode);
void redo(int game_mode);

#endif
