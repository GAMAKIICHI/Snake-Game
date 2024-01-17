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
    gfont = TTF_OpenFont("fonts/munro.ttf", 64);

    SDL_Rect destinationRect = {0, 0, gScreenSurface->w, gScreenSurface->h};
    SDL_RenderCopy(gRenderer, gTexture, NULL, &destinationRect);

    if(gfont == NULL)
    {
        printf("unable in initialize font! TTF_Error: %s\n", TTF_GetError());
    }

    gScreenSurface = TTF_RenderText_Solid(gfont, "Hello world", (SDL_Color){0x32, 0x32, 0xa8, 0xFF});

    if(gScreenSurface == NULL)
    {
        printf("unable to render text surface! SDL_Error: %s\n", SDL_GetError());
    }

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

    if(gTexture == NULL)
    {
        printf("unable to create texuture from surface! SDL_Error: %s\n", SDL_GetError());
    }
}