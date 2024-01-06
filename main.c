#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>

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
    EASY = 50,
    MEDIUM = 30,
    HARD = 25
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
SDL_Rect foodRect = {(int)NULL, (int)NULL, 16,16};

unsigned int lastMoved = 0;

typedef struct
{
    int x;
    int y;
} Position;

typedef struct Node
{
    Position value;
    struct Node *next;
}node_t;

typedef struct
{
    Position pos;
    Position sVel;
    node_t *body;
    unsigned int score;
} Snake;

typedef struct
{
    Position pos;
} Food;

void handleKeyEvent(SDL_Event *, Snake *);
void move(Snake *);
void renderSnake(Snake *);
void renderGrid();

void placeFood(Food *);
void renderFood(Food *);

bool checkCollision(SDL_Rect, SDL_Rect);

node_t *create_new_node(Position);
void printlist(node_t *);

int main(int argc, char *argv[])
{

    Snake playerSnake = {{((WIDTH/16) / 2) * 16,((HEIGHT/16) / 2) * 16}, {0,0}};
    Food food = {0,0};

    node_t *test;
    node_t *temp;

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

            renderGrid();
            move(&playerSnake);
            renderSnake(&playerSnake);

            if(checkCollision(snakeRect, foodRect))
            {
                printlist(playerSnake.body);
                placeFood(&food);
            }
            
            renderFood(&food);

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

void handleKeyEvent(SDL_Event *e, Snake *s)
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

void move(Snake *s)
{
    unsigned int currentTime = SDL_GetTicks();
    node_t *temp;

    if(currentTime - lastMoved >= EASY)
    {
        s->pos.x += s->sVel.x * 16;
        s->pos.y += s->sVel.y * 16;

        lastMoved = currentTime;
    }
}

void renderSnake(Snake *s)
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

void placeFood(Food *f)
{
    /*initialize rand*/
    srand(SDL_GetTicks());

    f->pos.x = (rand() % WIDTH / 16) * 16;
    f->pos.y = (rand() % HEIGHT / 16) * 16;

    //printf("(%d, %d)\n", f->pos.x, f->pos.y);
}

void renderFood(Food *f)
{
    foodRect.x = f->pos.x;
    foodRect.y = f->pos.y;

    SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
    SDL_RenderFillRect(gRenderer, &foodRect);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }
    return false;
}

node_t *create_new_node(Position value)
{
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

void printlist(node_t *head)
{
    node_t *temp = head;

    while(temp != NULL)
    {
        printf("[%d, %d] ", temp->value.x, temp->value.y);
        temp = temp->next;
    }
    printf("\n");
}
