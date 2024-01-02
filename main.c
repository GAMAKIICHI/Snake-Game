#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

enum KeyPress
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_TOTAL
};

/*Starts up SDL and creates window*/
bool init();

/*Frees media and shuts down SDL*/
void closeWindow();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Surface *gHelloWorld = NULL;

const int WIDTH = 480, HEIGHT = 360;

int main(int argc, char *argv[])
{
    /*Start up SDL and create window*/
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

        /*Update the surface*/
        SDL_UpdateWindowSurface(gWindow);

        

        /*Event handling*/
        SDL_Event e;
        bool quit = false;
        while(quit == false)
        {
            while(SDL_PollEvent(&e))
            {
                /*Quit Event*/
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }

                /*Arrow key input Event*/
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        printf("Up\n");
                        break;
                    case SDLK_DOWN:
                        printf("Down\n");
                        break;
                    case SDLK_RIGHT:
                        printf("Right\n");
                        break;
                    case SDLK_LEFT:
                        printf("Left\n");
                        break;
                }
            }
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
        gWindow = SDL_CreateWindow("SDL Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

void closeWindow()
{
    /*Deallocate surface*/
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    /*Destroy Window*/
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    /*Quit SDL subsystems*/
    SDL_Quit();
}