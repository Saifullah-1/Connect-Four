#include "Menu.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

void red (void) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,12);
}
void yellow(void) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,14);
}
void LightBlue (void) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,9);
}
void reset (void) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,15);
}
void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//The Frame Of the Menu
void frame(int height)
{
    gotoxy(40, 12);printf("%c", 201);
    gotoxy(40, 12 + height);printf("%c", 200);
    // upper and lower
    for (int i = 0; i <= 38; i++)
    {
        gotoxy(41 + i, 12);printf("%c", 205);
        gotoxy(41 + i, 12 + height);printf("%c", 205);
    }
    gotoxy(80, 12);printf("%c", 187);
    gotoxy(80, 12 + height);printf("%c", 188);
    // left and right
    for (int i = 1; i < height; i++)
    {
        gotoxy(40, 12 + i);printf("%c", 186);
        gotoxy(80, 12 + i);printf("%c", 186);
    }
}

void ShowConsoleCursor(int showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
//The Main Menu
int menu(void)
{
    ShowConsoleCursor(0);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int pos = 1;
    char ch;
    SetConsoleTextAttribute(console, 9);gotoxy(56, 10);printf("Main Menu");
    do
    {
        reset();
        gotoxy(53, 13);printf("[1] Start Game");
        gotoxy(53, 14);printf("[2] Load Game");
        gotoxy(53, 15);printf("[3] Top Scores");
        gotoxy(53, 16);printf("[4] Credit");
        gotoxy(53, 17);printf("[5] Exit");
        switch (pos)
        {
        case 1:
            red();gotoxy(53, 13);printf("[1] Start Game");
            break;
        case 2:
            red();gotoxy(53, 14);printf("[2] Load Game");break;
        case 3:
            red();gotoxy(53, 15);printf("[3] Top Scores");break;
        case 4:
            red();gotoxy(53, 16);printf("[4] Credit");break;
        case 5:
            red();gotoxy(53, 17);printf("[5] Exit");break;
        }
        ch = getch();
        if (ch == 72)
        {
            pos--;
            if (pos == 0)pos = 5;
        }
        if (ch == 80)
        {
            pos++;
            if (pos == 6)pos = 1;
        }
    } while (ch != 13);
    return (pos);
}

//The Game Mode Menu
int gameMode(void)
{

    ShowConsoleCursor(0);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int pos = 1;
    char ch;
    SetConsoleTextAttribute(console, 9);gotoxy(56, 10);printf("Game Mode");
    do
    {
        reset();
        gotoxy(43, 13);printf("[1] One Player Mode : VS. Computer");
        gotoxy(43, 14);printf("[2] Two Player Mode : VS. Human");
        switch (pos)
        {
        case 1:
            red();gotoxy(43, 13);printf("[1] One Player Mode : VS. Computer");break;
        case 2:
            red();gotoxy(43, 14);printf("[2] Two Player Mode : VS. Human");break;
        }
        ch = getch();
        if (ch == 72)
        {
            pos--;
            if (pos == 0)pos = 2;
        }
        if (ch == 80)
        {
            pos++;
            if (pos == 3)pos = 1;
        }
    } while (ch != 13);
    return (pos);
}