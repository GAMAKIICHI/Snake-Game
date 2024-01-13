#include "snake.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Renderer *gRenderer = NULL;

SDL_Rect foodRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect snakeRect = {(int)NULL, (int)NULL, 16,16};

unsigned int lastMoved = 0;

void handleKeyEvent(SDL_Event *e, Snake *s)
{  
    if(e->type == SDL_KEYDOWN)
    {
        /*this is needed so sVel doesnt go over 16*/
        s->sVel.x = 0;
        s->sVel.y = 0;

        switch(e->key.keysym.sym)
        {
            case SDLK_UP:
                s->sVel.y -= 16;
                s->sVel.x = 0;
                break;
            case SDLK_DOWN:
                s->sVel.y += 16;
                s->sVel.x = 0;
                break;
            case SDLK_RIGHT:
                s->sVel.x += 16;
                s->sVel.y = 0;
                break;
            case SDLK_LEFT:
                s->sVel.x -= 16;
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
        s->body->value.x += s->sVel.x;
        s->body->value.y += s->sVel.y;

        lastMoved = currentTime;
    }

    if (s->body->next != NULL && isInNewGrid(s->body->next->value, s->body->value))
    {
        shift(s->body);  
    }
}

/*
This functions renders the head of the snake.

function: renderSnake
param: body, ptr to body of snake
*/

void renderSnake(node_t *head)
{
    snakeRect.x = head->value.x;
    snakeRect.y = head->value.y;

    SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
    SDL_RenderFillRect(gRenderer, &snakeRect);
}

/*
This functions renders the body of the snake.
This works by ittering through each pos of the snake 
and rendering those one by one.

function: renderBody
param: body, ptr to body of snake
*/

void renderBody(node_t *body)
{
    node_t *temp = body->next;

    while(temp != NULL)
    {
        snakeRect.x = temp->value.x;
        snakeRect.y = temp->value.y;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x0, 0x0, 0xFF);
        SDL_RenderFillRect(gRenderer, &snakeRect);
        temp = temp->next;
    }
}

/*
This functions checks if two SDL_Rect
objects have overlapped

function: checkCollision
param: a, rect pos
       b, rect pos
returns: bool
*/

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }
    return false;
}

bool isInNewGrid(Position prev, Position current)
{

    /* These variables are divided by 16 to see the exact grid the snake head is currently in */
    prev.x = prev.x / 16;
    prev.y = prev.y / 16;

    current.x = current.x / 16;
    current.y = current.y / 16;

    if (prev.x != current.x || prev.y != current.y)
        return true;
    return false;

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