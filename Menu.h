#ifndef Menu
#define Menu
#include "Menu.c"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

void red(void);
void yellow(void);
void purple(void);
void reset(void);
void gotoxy(int x, int y);
void frame(int h);
void ShowConsoleCursor(int showFlag);
int menu(void);
int gameMode(void);

#endif