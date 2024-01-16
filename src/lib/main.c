#include <stdio.h>
#include "setup.h"
#include "scene_manager.h"
#include "snake.h"

int main(int argc, char *argv[])
{
    node_t *startPos = create_new_node((Position){((WIDTH/16)/2) * 16, ((HEIGHT/16)/2) * 16});
    playerSnake.body = startPos;

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

            if(!isGameOver(playerSnake))
            {
                gameScene();
            }

            /*Update Screen*/
            SDL_RenderPresent(gRenderer);
            // system("cls"); /*clear console*/
        }
    }
    
    /*Free resources and close SDL*/
    closeWindow();
    return 0;
}