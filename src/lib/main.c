#include <stdio.h>
#include "setup.h"
#include "scene_manager.h"
#include "snake.h"
#include "gamestate.h"

int main(int argc, char *argv[])
{

    initSnake();
    initFood();

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
        SDL_Keycode buttonEvent;

        /*Event handling*/
        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                /*Quit Event*/
                if(e.type == SDL_QUIT)
                    quit = true;
                
                handleKeyEvent(&e);
                buttonEvent = handleButtonEvents(&e);

            }

            /*clear screen*/
            SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0);
            SDL_RenderClear(gRenderer);

            switch(getGameState())
            {
                case MAINMENU:
                    mainMenuScene(buttonEvent);
                    break;
                case GAME:
                    gameScene();
                    break;
                case GAMEOVER:
                    gameOverScene(buttonEvent);
                    break;
                case SETTINGS:
                    break;
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