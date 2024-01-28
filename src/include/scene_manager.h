#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <SDL2/SDL_ttf.h>
#include "grid.h"
#include "snake.h"
#include "gamestate.h"
#include <stdbool.h>

typedef struct
{
    char fontPath[1000];
    int fontSize;
    SDL_Color color;
}FontSetting;

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

void mainMenuScene(SDL_Keycode btn);

void gameScene();

void gameOverScene(SDL_Keycode btn);

void settingsScene(SDL_Keycode btn);

void setColors();

SDL_Keycode handleButtonEvents(SDL_Event *e);

#endif