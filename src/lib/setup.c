#include "setup.h"

bool init()
{
    /*Initializtion flag*/
    bool success = true;

    /*Initialize SDL*/
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        /*Create window*/
        gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            // gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    /*Initialize TTF*/
    if(TTF_Init() < 0)
    {
        printf("TTF unable to initialize! TTF_Error: %s", TTF_GetError());
    }

    return success;
}

void closeWindow()
{
    /*Destroy Window*/
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    /*Quit SDL subsystems*/
    SDL_Quit();
}