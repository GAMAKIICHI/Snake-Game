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
SDL_Renderer *gRenderer = NULL;

const int WIDTH = 480, HEIGHT = 368;

int main(int argc, char *argv[])
{
    /*Start up SDL and create window*/
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
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

            /*clear screen*/
            SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0);
            SDL_RenderClear(gRenderer);

            /*render grid*/
            for(int row = 0; row <= HEIGHT; row+=16)
            {
                for(int col = 0; col <= WIDTH; col+=16)
                {
                    SDL_Rect fillRect = {col,row,16,16};
                    SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
                    SDL_RenderDrawRect(gRenderer, &fillRect);
                }
            }

            /*Update Screen*/
            SDL_RenderPresent(gRenderer);
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