#include <stdio.h>
#include <stdlib.h>
#include "systemCommands.h"
#define DEBUG
int main(int argc, char *argv[]) {
    int miniTouchResult = mini_touch("newFILOU.txt");
    //int miniClean = mini_clean("newFIIIILE.txt");
    #ifdef DEBUG
    printf("Fichier cré ? %i", miniTouchResult);
    #endif
    mini_grep("newFIIIILE.txt","bonjour");
    wc("newFIIIILE.txt");
    mini_exit();
    return 0;
}