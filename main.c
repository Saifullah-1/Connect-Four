#include "Menu.h"

int main_menu_choice = 1;
int gameMode_menu_choice = 1;

int main()
{
mainmenu:
    reset();

    system("cls");
    frame(6);
    main_menu_choice = menu(); // selection is the variable that contains the player's choice from the main menu
    // return default colour
    reset();
    system("cls");
    switch (main_menu_choice)
    {
    case 1:
        system("cls");
        // create a frame contains 2 rows (choices)
        frame(3);
        gameMode_menu_choice = gameMode();
        switch (gameMode_menu_choice)
        {
        case 1:
            reset();
            system("cls");
            printf("Hello");
            break;
        }
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4: //[4]Credit 
        system("cls");
        yellow();
        printf("This Is Our Final Project 'Connect 4 Game'\nWe Wish You Enjoy Our Model.\n\nBY : Ahmed Ashraf & Saifullah Mousaad\n");
        printf("Please Press 0 To Visit Our GIT https://github.com/Saifullah-1/Connect4\n");
        printf("Press 1 To Return To The Main Menu ... ");
        int n; // n = scan 1 **make a function to scan valid value
        scanf("%i", &n);
        if (n == 1)
        {
            goto mainmenu;
        }
        else if (n == 0)
        {
            system("START https://github.com/Saifullah-1/Connect4");
            goto mainmenu;
        }
        break;
    case 5:
        exit(-1);
        break;
    }
}