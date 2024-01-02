#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/*Starts up SDL and creates window*/
bool init();

/*Loads media*/
bool loadMedia();

/*Frees media and shits down SDL*/
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
        /*Load media*/
        if(!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            /*Apply the image*/
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            /*Update the surface*/
            SDL_UpdateWindowSurface(gWindow);

            //Hack for window to stay up
            SDL_Event e;
            bool quit = false;
            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
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

bool loadMedia()
{
    /*Loading success flag*/
    bool success = true;

    /*Load splash image*/
    gHelloWorld = SDL_LoadBMP("480-360-sample.bmp");
    if(gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "480-360-sample.bmp", SDL_GetError());
        success = false;
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