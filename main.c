#include "Menu.h"
#include "GameLoop.h"
// #include "SaveAndLoad .c"

void main()
{
    int t = 0;
    XML();
    int main_menu_choice;
    int gameMode_menu_choice;
    int ingame_menu_choice;
    int aftergame_menu_choice;
    int save_menu_choice;
    int load_menu_choice;
mainmenu:
    main_menu_choice = 1;
    gameMode_menu_choice = 1;
    ingame_menu_choice = 1;
    aftergame_menu_choice = 1;
    save_menu_choice = 1;
    load_menu_choice = 1;
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
            ShowConsoleCursor(1);
            resetPlayerTurnArr(3);
            playerData(1);
            startGame();
            start = clock();
            while (checkFreeSpaces() != 0)
            {
            game:
                i = Player1.PlayerScore;
                j = Player2.PlayerScore;
                ingame_menu_choice = inGameMenu();
                switch (ingame_menu_choice)
                {
                case 1:
                    break;
                case 2:
                    undo(1);
                    printBoard();
                    checkScore();
                    playerData(1);
                    end = clock();
                    Time(start, end);
                    goto game;
                case 3:
                    redo(1);
                    printBoard();
                    checkScore();
                    playerData(1);
                    end = clock();
                    Time(start, end);
                    goto game;
                case 4:
                    save_menu_choice = saveMenu();
                case 5:
                    goto mainmenu;
                }
                playerMove();
                printBoard();
                checkScore();
                Player1.PlayerScore -= i;
                Player2.PlayerScore -= j;
                i = Player1.PlayerScore;
                j = Player2.PlayerScore;
                end = clock();
                Time(start, end);
                playerData(1);
                // Sleep(500);
                computerMove();
                printBoard();
                checkScore();
                Player1.PlayerScore -= i;
                Player2.PlayerScore -= j;
                end = clock();
                Time(start, end);
                playerData(1);
            }
            checkWinner(1);
            reset();
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
        case 2:
            ShowConsoleCursor(1);
            resetPlayerTurnArr(2);
            playerData(2);
            startGame();
            start = clock();
        afterload:
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
                    playerData(2);
                    end = clock() + t;
                    Time(start, end);
                    goto gamemenu;
                case 3:
                    redo(2);
                    printBoard();
                    checkScore();
                    playerData(2);
                    end = clock() + t;
                    Time(start, end);
                    goto gamemenu;
                    break;
                case 4:
                    save_menu_choice = saveMenu();
                    switch (save_menu_choice)
                    {
                    case 1:
                        file_save(1, conf.height, conf.width/*, position_array*/, turn, Player1.PlayerMoves, Player2.PlayerMoves, Player1.PlayerScore, Player2.PlayerScore/*, board*/, end);
                        break;
                    case 2:
                        file_save(2, conf.height, conf.width/*, position_array*/, turn, Player1.PlayerMoves, Player2.PlayerMoves, Player1.PlayerScore, Player2.PlayerScore/*, board*/, end);
                        break;
                    case 3:
                        file_save(3, conf.height, conf.width/*, position_array*/, turn, Player1.PlayerMoves, Player2.PlayerMoves, Player1.PlayerScore, Player2.PlayerScore/*, board*/, end);
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
                end = clock() + t;
                Time(start, end);
                playerData(2);
            }
            checkWinner(2);
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
            Load(1);
            if (ok == 0)
            {
                int check = 0;
                do
                {
                    system("cls");
                    printf("There Is No Saved File In This Slot\n\n");
                    printf("Please Enter [1] To Go To Main Menu ");
                    scanf("%d", &check);
                    printf("\n\n");
                } while (check != 1);
                goto mainmenu;
            }
            else if (ok == 1)
            {
                system("cls");
                resetBoard();
                printBoard();
                resetPlayerData();
                resetUndoArray();
                ShowConsoleCursor(1);
                resetPlayerTurnArr(2);
                playerData(2);
                startGame();
                Load(1);
                checkFreeSpaces();
                printBoard();
                playerData(2);
                Player1.PlayerMoves = info[0];
                Player2.PlayerMoves = info[1];
                Player1.PlayerScore = info[2];
                Player2.PlayerScore = info[3];
                turn = info[4];
                t = info[5];
                CheckPlaces();
                playerData(2);

                goto afterload;
                break;
            }

        case 2:
            Load(2);
            if (ok == 0)
            {
                int check = 0;
                do
                {
                    system("cls");
                    printf("There Is No Saved File In This Slot\n\n");
                    printf("Please Enter [1] To Go To Main Menu ");
                    scanf("%d", &check);
                    printf("\n\n");

                } while (check != 1);
                goto mainmenu;
            }
            else if (ok == 1)
            {
                resetBoard();
                printBoard();
                resetPlayerData();
                resetUndoArray();
                ShowConsoleCursor(1);
                resetPlayerTurnArr(2);
                playerData(2);
                startGame();
                Load(2);
                printBoard();
                playerData(2);
                Player1.PlayerMoves = info[0];
                Player2.PlayerMoves = info[1];
                Player1.PlayerScore = info[2];
                Player2.PlayerScore = info[3];
                turn = info[4];
                t = info[5];
                CheckPlaces();
                playerData(2);
                goto afterload;
                break;
            }
        case 3: //[3]File 3
            Load(3);
            if (ok == 0)
            {
                int check = 0;
                do
                {
                    system("cls");
                    printf("There Is No Saved File In This Slot\n\n");
                    printf("Please Enter [1] To Go To Main Menu ");
                    scanf("%d", &check);
                    printf("\n\n");
                } while (check != 1);
                goto mainmenu;
            }
            else if (ok == 1)
            {
                system("cls");
                resetBoard();
                printBoard();
                resetPlayerData();
                resetUndoArray();
                ShowConsoleCursor(1);
                resetPlayerTurnArr(2);
                playerData(2);
                startGame();
                Load(3);
                printBoard();
                playerData(2);
                Player1.PlayerMoves = info[0];
                Player2.PlayerMoves = info[1];
                Player1.PlayerScore = info[2];
                Player2.PlayerScore = info[3];
                turn = info[4];
                t = info[5];
                CheckPlaces();
                playerData(2);
                goto afterload;
                break;
            }
        }
        break;
    case 3:
        callTopScores(conf.scores);
        printf("\n\n");
        int check;
        printf("Please Enter [1] To Go To Main Menu ");
        scanf("%d", &check);
        while (check != 1)
        {
            printf("Wrong Entry , Please Enter [1] To Go To Main Menu ");
            scanf("%d", &check);
        }
        goto mainmenu;
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
