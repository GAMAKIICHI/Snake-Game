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
        SDL_Keycode sceneKeyEvents;

        /*Event handling*/
        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                /*Quit Event*/
                if(e.type == SDL_QUIT)
                    quit = true;
                
                handleKeyEvent(&e);
                sceneKeyEvents = handleButtonEvents(&e);

            }

            /*clear screen*/
            SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0);
            SDL_RenderClear(gRenderer);

            switch(getGameState())
            {
                case MAINMENU:
                    mainMenuScene(sceneKeyEvents);
                    break;
                case GAME:
                    gameScene();
                    break;
                case GAMEOVER:
                    gameOverScene(sceneKeyEvents);
                    break;
                case SETTINGS:
                    settingsScene(sceneKeyEvents);
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