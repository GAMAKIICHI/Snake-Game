#include "gamestate.h"

static enum SCENES gameState = MAINMENU;

bool quit = false;

void setGameState(enum SCENES scene)
{
    gameState = scene;
}

enum SCENES getGameState()
{
    return gameState;
}