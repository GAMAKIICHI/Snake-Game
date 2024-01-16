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

void mainMenuScene();

void gameScene();

void gameOverScene();

#endif