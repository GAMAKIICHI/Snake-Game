#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <SDL2/SDL_ttf.h>
#include "snake.h"
#include "grid.h"

typedef struct 
{
    void *scene;
    struct Scenes *prev, *next;

}Scenes;

typedef struct
{
    char fontPath[1000];
    int fontSize;
    SDL_Color color;
}FontSetting;

typedef struct 
{
    int width;
    int height;
    int fontSize;
    SDL_Color color;
    SDL_Color focus;
    
}ButtonSettings;


int mainMenuScene(SDL_Keycode btn);

void gameScene();

int gameOverScene(SDL_Keycode btn);

SDL_Keycode handleButtonEvents(SDL_Event *e);

#endif