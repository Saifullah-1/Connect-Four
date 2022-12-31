#ifndef MENUS /*Header Guard*/
#define MENUS
#include "Menu .c"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>

void red(void);
void yellow(void);
void LightBlue(void);
void reset(void);
void gotoxy(int x, int y);
void frame(int h);
void ShowConsoleCursor(int showFlag);
int menu(void);
int gameMode(void);
int loadMenu(void);
void credit(void);
void startGame(void);
int inGameMenu(void);
int saveMenu(void);
int afterGame(void);

#endif