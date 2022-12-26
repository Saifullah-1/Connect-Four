#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "Menu.h"
#include "GameLoop.h"
// #include "SaveAndLoad.h"
int main_menu_choice = 1;
int gameMode_menu_choice = 1;
int ingame_menu_choice = 1;
int aftergame_menu_choice = 1;

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

            break;
        case 2:
            system("cls");
            int start = clock();
            resetBoard();
            resetPlayerData();
            resetPlayerTurnArr();
            resetColumnFreeSpacesArr();
            printBoard();
            playerData();
            startGame();
            while (checkFreeSpaces() != 0)
            {
                // system("cls");
                int i = Player1.PlayerScore;
                int j = Player2.PlayerScore;
                ingame_menu_choice = inGameMenu();
                switch (ingame_menu_choice)
                {
                case 1:
                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:

                    break;
                case 5:
                    goto mainmenu;
                    break;
                }
                playerMove();
                printBoard();
                checkScore();
                Player1.PlayerScore -= i;
                Player2.PlayerScore -= j;
                int end = clock();
                Time(start, end);
                playerData();
            }
            Instant_Save(Player1.PlayerScore, Player2.PlayerScore);
            checkWinner();
            system("cls");
            printBoard();
            playerData();
            aftergame_menu_choice = afterGame();
            if (aftergame_menu_choice==1)
            {
                goto mainmenu;
            }else
            {
                exit(-1);
            }
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
    credit:
        system("cls");
        yellow();
        printf("This Is Our Final Project 'Connect 4 Game'\nWe Wish You Enjoy Our Model.\n\nBY : Ahmed Ashraf & Saifullah Mousaad\n\n");
        printf("Please Press 0 To Visit Our GITHUB : https://github.com/Saifullah-1/Connect4\n");
        printf("OR Press 1 To Return To The Main Menu ... ");
        int n;
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
        else
        {
            goto credit;
        }

        break;
    case 5:
        exit(-1);
        break;
    }
}
