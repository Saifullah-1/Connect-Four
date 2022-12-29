#include "Menu.h"
int no_of_scores=10;//read from xml file


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
/*The Main Menu*/

int menu(void)
{
    ShowConsoleCursor(0);
    int pos = 1;
    char ch;
    LightBlue();gotoxy(56, 10);printf("Main Menu");
    do
    {
        reset();
        gotoxy(53, 13);printf("[1] Start Game");
        gotoxy(53, 14);printf("[2] Load Game");
        gotoxy(53, 15);printf("[3] Top %i Players", no_of_scores);
        gotoxy(53, 16);printf("[4] Credit");
        gotoxy(53, 17);printf("[5] Quit");
        switch (pos)
        {
        case 1:
            red();gotoxy(53, 13);printf("[1] Start Game");
            break;
        case 2:
            red();gotoxy(53, 14);printf("[2] Load Game");break;
        case 3:
            red();gotoxy(53, 15);printf("[3] Top %i Players", no_of_scores);break;
        case 4:
            red();gotoxy(53, 16);printf("[4] Credit");break;
        case 5:
            red();gotoxy(53, 17);printf("[5] Quit");break;
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
    int pos = 1;
    char ch;
    LightBlue();gotoxy(56, 10);printf("Game Mode");
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
int loadMenu(void)
{
    int choice;
    char userInput[100];
    gotoxy(45,10);LightBlue();
    printf("Loading Menu");
    while (1)
    {
        reset();
        gotoxy(10, 15);
        printf("                                                                                                                                          ");
        gotoxy(10, 15);
        printf("Please Enter The File You Want To Load [1]File 1....[2]File 2....[3]File 3 >> ");
        gets(userInput);
        char x = userInput[0];
        if (strlen(userInput) == 1 && x - 48 >= 1 && x - 48 <= 3)
        {
            gotoxy(0, 15);
            printf("                                                                                                                                      ");
            choice = x - 48;
            break;
        }
    }
    return (choice);
}
void credit(void){
        system("cls");
        yellow();
        printf("This Is Our Final Project 'Connect 4 Game'\nWe Wish You Enjoy Our Model.\n\nBY : Ahmed Ashraf & Saifullah Mousaad\n\n");
        reset();
        printf("Please Enter [0] To Visit Our GITHUB : https://github.com/Saifullah-1/Connect4\n");
        printf("OR Enter [1] To Return To The Main Menu ... ");
        int n;
        scanf("%i", &n);
        if (n == 0)
        {
            system("START https://github.com/Saifullah-1/Connect4");
        }
        else if (n !=0&&n!=1)
        {
            credit();
        }
}
