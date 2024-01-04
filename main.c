#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 480
#define HEIGHT 368

enum KeyPress
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_TOTAL
};

enum Difficulty
{
    EASY = 200,
    MEDIUM = 150,
    HARD = 50
};

/*Starts up SDL and creates window*/
bool init();

/*Frees media and shuts down SDL*/
void closeWindow();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Renderer *gRenderer = NULL;

SDL_Rect gridRect = {(int)NULL,(int)NULL,16,16};
SDL_Rect snakeRect = {(int)NULL, (int)NULL, 16,16};

unsigned int lastMoved = 0;

struct Position
{
    int x;
    int y;
};

struct Snake
{
    struct Position pos;
    struct Position sVel;
    struct Position tail[(WIDTH / 16) * (HEIGHT / 16)];
    unsigned int score;
};

void handleKeyEvent(SDL_Event *, struct Snake *);
void move(struct Snake *);
void renderSnake(struct Snake *);
void renderGrid();

int main(int argc, char *argv[])
{
    struct Snake playerSnake = {{0,0}, {0,0}, {(int)NULL, (int)NULL}, 0};

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

            renderGrid();
            move(&playerSnake);
            renderSnake(&playerSnake);

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

void handleKeyEvent(SDL_Event *e, struct Snake *s)
{
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP:
                s->sVel.y -= 1;
                s->sVel.x = 0;
                break;
            case SDLK_DOWN:
                s->sVel.y += 1;
                s->sVel.x = 0;
                break;
            case SDLK_RIGHT:
                s->sVel.x += 1;
                s->sVel.y = 0;
                break;
            case SDLK_LEFT:
                s->sVel.x -= 1;
                s->sVel.y = 0;
                break;
        }
    }
    
}

void move(struct Snake *s)
{
    unsigned int currentTime = SDL_GetTicks();
    
    if(currentTime - lastMoved >= HARD)
    {
        s->pos.x += s->sVel.x * 16;
        s->pos.y += s->sVel.y * 16;
        lastMoved = currentTime;
    }
}

void renderSnake(struct Snake *s)
{
    snakeRect.x = s->pos.x;
    snakeRect.y = s->pos.y;

    SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
    SDL_RenderFillRect(gRenderer, &snakeRect);
}

void renderGrid()
{
    for(int row = 0; row <= HEIGHT; row+=16)
    {
        for(int col = 0; col <= WIDTH; col+=16)
        {
            gridRect.x = col;
            gridRect.y = row;
            SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
            SDL_RenderDrawRect(gRenderer, &gridRect);
        }
    }
}