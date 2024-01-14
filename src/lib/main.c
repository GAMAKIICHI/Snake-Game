#include <stdio.h>
#include <SDL2/SDL.h>
#include "snake.h"
#include "grid.h"

/*Starts up SDL and creates window*/
bool init();

/*Frees media and shuts down SDL*/
void closeWindow();

int main(int argc, char *argv[])
{
    node_t *startPos = create_new_node((Position){((WIDTH/16)/2) * 16, ((HEIGHT/16)/2) * 16});

    Snake playerSnake = {startPos, {0,0}, 0, EASY};
    Food food = {0,0};

    /*Place first piece of food*/
    placeFood(&food);

    /*Start up SDL and create window*/
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        /*Update the surface*/
        SDL_UpdateWindowSurface(gWindow);

        SDL_Event e;
        bool quit = false;

        /*Event handling*/
        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                /*Quit Event*/
                if(e.type == SDL_QUIT)
                    quit = true;
                
                handleKeyEvent(&e, &playerSnake);

            }

            /*clear screen*/
            SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0);
            SDL_RenderClear(gRenderer);

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
            }

            // printlist(playerSnake.body);
            renderGrid();
            renderFood(&food);

            /*Update Screen*/
            SDL_RenderPresent(gRenderer);
            // system("cls"); /*clear console*/
        }
    }
    
    /*Free resources and close SDL*/
    closeWindow();
    return 0;
}

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
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
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
