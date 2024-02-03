#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <SDL2/SDL_ttf.h>
#include "grid.h"
#include "snake.h"
#include "gamestate.h"
#include <stdbool.h>
#include <audio.h>
#include <settings.h>

typedef struct
{
    char fontPath[1000];
    int numSound;
    int xOffset;
    int posY;
    SDL_Color color;
    SDL_Color focus;
    bool isFocus;

}barSettings;

void mainMenuScene();

void gameScene();

void gameOverScene();

void settingsScene();

void setColors();

void resetSelectedButton();

void handleButtonEvents(SDL_Event *e);

#endif