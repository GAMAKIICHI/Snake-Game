#include "scene_manager.h"

void gameScene()
{
    /*update the pos of the snake*/
    move(&playerSnake);
    renderSnakeHead(playerSnake.body);
    renderBody(playerSnake.body);

    /*Check whether the snake head has collided with food*/
    if(checkCollision(snakeRect, foodRect))
    {
        /*Add new body node*/
        insertNodeAtEnd(playerSnake.body);
        placeFood(&food);
        playerSnake.score++;
    }

    // printlist(playerSnake.body);
    renderGrid();
    renderFood(&food);
}

void gameOverScene()
{
    TTF_Font *gfont = NULL;
    gfont = TTF_OpenFont("fonts/munro.ttf", 16);
    gScreenSurface = TTF_RenderText_Solid(gfont, "Hello world", (SDL_Color){0x32, 0x32, 0xa8, 0xFF});

    SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

    SDL_FreeSurface(gScreenSurface);
}