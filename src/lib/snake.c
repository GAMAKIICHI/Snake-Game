#include "snake.h"

unsigned int lastMoved = 0;

static settings defaultSettings = {16, {0x1C, 0xFC, 0x3, 0xFF}, EASY};

static Snake *snake;
static Food *food;

void initFood()
{
    /*Allocating memory for snake*/
    food = malloc(sizeof(Food));

    if(snake == NULL)
    {
        printf("Unable to init Food!\n");
        return;
    }

    food->pos = (Position){0,0};
    food->size = defaultSettings.size;
}

void placeFood()
{
    /*initialize rand*/
    srand(SDL_GetTicks());

    food->pos.x = (rand() % WIDTH / food->size) * food->size;
    food->pos.y = (rand() % HEIGHT / food->size) * food->size;
}

void renderFood()
{
    foodRect.x = food->pos.x;
    foodRect.y = food->pos.y;

    SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
    SDL_RenderFillRect(gRenderer, &foodRect);
}

void initSnake()
{
    /*Allocating memory for snake*/
    snake = malloc(sizeof(Snake));

    if(snake == NULL)
    {
        printf("Unable to init snake!\n");
        return;
    }

    node_t *newHead = create_new_body_node((Position){((WIDTH/defaultSettings.size)/2) * defaultSettings.size, ((HEIGHT/defaultSettings.size)/2) * defaultSettings.size});

    snake->body = newHead;
    snake->sVel = (Position){0,0};
    snake->score = 0;
    snake->difficulty = defaultSettings.difficulty;
    snake->size = defaultSettings.size;
    snake->color = defaultSettings.color;
}

Position handleKeyEvent(SDL_Event *e)
{  
    if(e->type == SDL_KEYDOWN)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP:
                snake->sVel = (Position){0, -16};
                break;
            case SDLK_DOWN:
                snake->sVel = (Position){0, 16};
                break;
            case SDLK_RIGHT:
                snake->sVel = (Position){16, 0};
                break;
            case SDLK_LEFT:
                snake->sVel = (Position){-16, 0};
                break;
        }
    }
    
}

void move()
{
    unsigned int currentTime = SDL_GetTicks();

    if(currentTime - lastMoved >= snake->difficulty)
    {
        /*updates head of linked list that stores pos of head of snake*/
        snake->body->pos.x += snake->sVel.x;
        snake->body->pos.y += snake->sVel.y;

        lastMoved = currentTime;
    }

}

/*
This functions renders the head of the snake.

function: renderSnake
param: body, ptr to body of snake
*/

void renderSnakeHead()
{
    snakeRect.x = snake->body->pos.x;
    snakeRect.y = snake->body->pos.y;

    SDL_SetRenderDrawColor(gRenderer, snake->color.r, snake->color.g, snake->color.b, snake->color.a);
    SDL_RenderFillRect(gRenderer, &snakeRect);
}

void checkBoundaries()
{
    switch(snake->difficulty)
    {
        case EASY:
            if(snake->body->pos.x < 0)
                snake->body->pos.x = WIDTH;
            else if(snake->body->pos.x > WIDTH)
                snake->body->pos.x = 0;
            else if(snake->body->pos.y < GRIDOFFSET)
                snake->body->pos.y = HEIGHT;
            else if(snake->body->pos.y > HEIGHT)
                snake->body->pos.y = GRIDOFFSET;
            break;
    }
}

int getScore()
{
    return snake->score;
}

/*
This functions allocates space for a new node,
and sets the next last node to null.

function: creat_new_node
param: pos, current pos when added to body
returns: node_t
*/

node_t *create_new_body_node(Position pos)
{
    /*allocate memory for new node*/
    node_t *result = malloc(sizeof(node_t));

    result->pos = pos;
    result->next = NULL;
    return result;
}

/*
This functions finds the last pos in body 
of the snake, and adds a new node for body piece.

function: insertNodeAtEnd
param: head, ptr to body of snake
       pos, current pos when added to body
*/

void insertBodyNode(node_t *head)
{
    node_t *temp;
    Position newPos;

    if(head == NULL)
        return;

    temp = head;

    /*this goes through the linked list till it reaches the last element*/
    while(temp->next != NULL)
    {
        temp = temp->next;
        newPos = temp->pos;
    }
    temp->next = create_new_body_node(newPos);
}

void printlist(node_t *head)
{
    node_t *temp = head;
    while(temp != NULL)
    {
        printf("[%d, %d]->", temp->pos.x, temp->pos.y);
        temp = temp->next;
    }

    printf("NULL\n");
}

void testBody()
{
    node_t *head = NULL;
    node_t *temp;
}