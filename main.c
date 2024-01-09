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
    node_t *body;
    Position sVel;
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
void insertNodeAtEnd(node_t *, Position);
void shift(node_t *);
void printlist(node_t *);

void renderBody(Snake *);

void testBody()
{
    node_t *head = NULL;
    node_t *temp;

    head = create_new_node((Position){0,0});

    for(int i = 1; i < 10; i++)
    {
        if(head == NULL)
            return;

        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = create_new_node((Position){i,i});
    }
    printlist(head);
}

int main(int argc, char *argv[])
{

    node_t *startPos = create_new_node((Position){((WIDTH/16)/2) * 16, ((HEIGHT/16)/2) * 16});

    Snake playerSnake = {startPos, {0,0}, 0};
    Food food = {0,0};

    testBody()

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

            /*Check whether the snake head has collided with food*/
            if(checkCollision(snakeRect, foodRect))
            {
                /*Add new body node*/
                insertNodeAtEnd(playerSnake.body, playerSnake.body->value);
                placeFood(&food);
            }
            
            // printlist(playerSnake.body);

            renderBody(&playerSnake);
            //printlist(playerSnake.body);

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

    if(currentTime - lastMoved >= EASY)
    {
        /*updates head of linked list that stores pos of head of snake*/
        s->body->value.x += s->sVel.x * 16;
        s->body->value.y += s->sVel.y * 16;

        lastMoved = currentTime;
    }
}

void renderSnake(Snake *s)
{
    snakeRect.x = s->body->value.x;
    snakeRect.y = s->body->value.y;

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
    /*allocate memory for new node*/
    node_t *result = malloc(sizeof(node_t));

    result->value = value;
    result->next = NULL;
    return result;
}

void printlist(node_t *head)
{
    node_t *temp = head;

    system("cls"); /*clear console*/
    while(temp != NULL)
    {
        printf("[%d, %d]->", temp->value.x, temp->value.y);
        temp = temp->next;
    }

    printf("NULL\n");
}

void renderBody(Snake *s)
{
    node_t *temp = s->body;

    while(temp != NULL)
    {
        snakeRect.x = temp->value.x;
        snakeRect.y = temp->value.y;

        SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
        SDL_RenderFillRect(gRenderer, &snakeRect);
        temp = temp->next;
    }
}

/*
This functions finds the last pos in body 
of the snake, and adds a new node for body piece.

function: insertNodeAtEnd
param: head, ptr to body of snake
       pos, current pos when added to body
*/

void insertNodeAtEnd(node_t *head, Position pos)
{
    node_t *temp;

    if(head == NULL)
        return;

    temp = head;

    /*this goes through the linked list till it reaches the last element*/
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = create_new_node(pos);
}

void shift(node_t *body)
{
    if(body == NULL)
    {
        return;
    }

    node_t *temp = body;
    node_t *prev = temp->next;

    while(temp != NULL)
    {
        prev = temp;
        temp = temp->next;
        prev = temp->next;
    }

}
