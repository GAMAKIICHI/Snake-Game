#include "gamestate.h"

static enum SCENES gameState = MAINMENU;

bool quit = false;

void setGameState(enum SCENES scene)
{
    gameState = scene;
    resetSelectedButton(); /*resets selected buttton back to 0*/
}

enum SCENES getGameState()
{
    return gameState;
}