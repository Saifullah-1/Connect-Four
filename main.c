#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include "Menu.h"
#include "GameLoop.h"
#include "SaveAndLoad.h"
#include "Menu.c"


void main()
{
    int main_menu_choice;
    int gameMode_menu_choice;
    int ingame_menu_choice;
    int aftergame_menu_choice;
    int save_menu_choice;
mainmenu:
    main_menu_choice = 1;
    gameMode_menu_choice = 1;
    ingame_menu_choice = 1;
    aftergame_menu_choice = 1;
    save_menu_choice = 1;
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
        //  create a frame contains 2 rows (choices)
        frame(3);
        gameMode_menu_choice = gameMode();
        system("cls");
        resetBoard();
        resetPlayerData();
        resetColumnFreeSpacesArr();
        resetUndoArray();
        printBoard();
        int start;
        int end, i, j;
        switch (gameMode_menu_choice)
        {
        case 1:
            resetPlayerTurnArr(3);
            break;
        case 2:
            ShowConsoleCursor(1);
            resetPlayerTurnArr(2);
            playerData();
            startGame();
            start = clock();
            while (checkFreeSpaces() != 0)
            {
            gamemenu:
                i = Player1.PlayerScore;
                j = Player2.PlayerScore;
                ingame_menu_choice = inGameMenu();
                switch (ingame_menu_choice)
                {
                case 1:
                    break;
                case 2:
                    undo(2);
                    printBoard();
                    checkScore();
                    playerData();
                    end = clock();
                    Time(start, end);
                    goto gamemenu;
                case 3:
                    redo(2);
                    printBoard();
                    checkScore();
                    playerData();
                    end = clock();
                    Time(start, end);
                    goto gamemenu;
                    break;
                case 4:
                    save_menu_choice = saveMenu();
                    switch (save_menu_choice)
                    {
                    case 1:
                        file_save(1,rows,colmns,position_array,turn,Player1.PlayerMoves,Player2.PlayerMoves,Player1.PlayerScore,Player2.PlayerScore,board);
                        break;
                    case 2:
                        file_save(2,rows,colmns,position_array,turn,Player1.PlayerMoves,Player2.PlayerMoves,Player1.PlayerScore,Player2.PlayerScore,board);
                        break;
                    case 3:
                        file_save(3,rows,colmns,position_array,turn,Player1.PlayerMoves,Player2.PlayerMoves,Player1.PlayerScore,Player2.PlayerScore,board);
                        break;
                    }
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
                end = clock();
                Time(start, end);
                playerData();
            }
            // Instant_Save(Player1.PlayerScore, Player2.PlayerScore);
            checkWinner();
            reset();
            // system("cls");
            // printBoard();
            // playerData();
            aftergame_menu_choice = afterGame();
            if (aftergame_menu_choice == 1)
            {
                goto mainmenu;
            }
            else
            {
                exit(-1);
            }
            break;
        }
        break;
    case 2:
        ShowConsoleCursor(1);
        load_menu_choice = loadMenu();
        switch (load_menu_choice)
        {
        case 1: //[1]File 1
            /* code */
            break;

        case 2: //[2]File 2
            break;
        case 3: //[3]File 3

            break;
        }
        break;
    case 3:
        /* code */
        break;
    case 4: //[4]Credit
        credit();
        goto mainmenu;
        break;
    case 5:
        exit(-1);
        break;
    }
}
