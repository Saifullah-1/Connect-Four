#include "SaveAndLoad.h"
#include "SaveAndLoad.h"
#include "GameLoop.c"
void file_save(int file_number)
{ // file number from save menu
    if (file_number == 1)
    {
        FILE *f1;
        f1 = fopen("savegame1.bin", "wb");
        save(f1);
        fclose(f1);
    }
    else if (file_number == 2)
    {
        FILE *f2;
        f2 = fopen("savegame2.bin", "wb");
        save(f2);
        fclose(f2);
    }
    else if (file_number == 3)
    {
        FILE *f3;
        f3 = fopen("savegame3.bin", "wb");
        save(f3);
        fclose(f3);
    }
}
void save(FILE *f){
    fwrite(Player1.PlayerScore, 1, sizeof(Player1.PlayerScore), f);fwrite(Player1.PlayerMoves, 1, sizeof(Player1.PlayerMoves), f);
}
