#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <SDL2/SDL_ttf.h>
#include "grid.h"
#include "snake.h"
#include "gamestate.h"

typedef struct
{
    char fontPath[1000];
    int fontSize;
    SDL_Color color;
}FontSetting;

int mainMenuScene(SDL_Keycode btn);

void gameScene();

int gameOverScene(SDL_Keycode btn);

SDL_Keycode handleButtonEvents(SDL_Event *e);

#endif