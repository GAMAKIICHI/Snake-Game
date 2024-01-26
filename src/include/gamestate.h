#ifndef GAMESTATE
#define GAMESTATE

#include <stdbool.h>

enum SCENES
{
    MAINMENU,
    GAME,
    GAMEOVER,
    SETTINGS
};

extern bool quit;

void setGameState(enum SCENES scene);

enum SCENES getGameState();

#endif