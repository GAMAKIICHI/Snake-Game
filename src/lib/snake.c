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

    food->size = defaultSettings.size;
    food->pos = generateRandomPos(time(NULL));
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

    /*init snake position to the center of the grid*/
    node_t *newHead = create_new_body_node((Position){((WIDTH/defaultSettings.size)/2) * defaultSettings.size, ((HEIGHT/defaultSettings.size)/2) * defaultSettings.size});

    snake->body = newHead;
    snake->sVel = (Position){0,0};
    snake->score = 0;
    snake->difficulty = defaultSettings.difficulty;
    snake->size = defaultSettings.size;
    snake->color = defaultSettings.color;
}

void placeFood()
{
    /*Checks if the snake rect and the food rect have collided*/
    if(SDL_HasIntersection(&snakeRect, &foodRect))
    {
        insertBodyNode(food->pos);
        food->pos = generateRandomPos(SDL_GetTicks());
        snake->score++;
    }
}

void renderFood()
{
    foodRect.x = food->pos.x;
    foodRect.y = food->pos.y;

    SDL_SetRenderDrawColor(gRenderer, 0x1C, 0xFC, 0x3, 0xFF);
    SDL_RenderFillRect(gRenderer, &foodRect);
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

static Position generateRandomPos(int seed)
{

    /*initialize rand*/
    srand(seed);

    Position newPos = {(rand() % WIDTH) / food->size * food->size, (rand() % (HEIGHT - GRIDOFFSET  + 1) + GRIDOFFSET) / food->size * food->size};
    return newPos;

}

void move()
{
    if(snake->body == NULL)
    {
        printf("There is no snake body!\n");
        return;
    }

    unsigned int currentTime = SDL_GetTicks();

    /*Updates the position of the snake after a certain time in ms. See difficulty for ms*/
    if(currentTime - lastMoved >= snake->difficulty)
    {   
        moveBody();

        /*updates head of linked list that stores pos of head of snake*/
        snake->body->pos.x += snake->sVel.x;
        snake->body->pos.y += snake->sVel.y;

        lastMoved = currentTime;
    }
}

static void moveBody()
{
     if(snake->body == NULL || snake->body->next == NULL)
    {
        printf("There is no snake body to move!\n");
        return;
    }

    if(snake->body->pos.x != snake->body->next->pos.x|| snake->body->pos.y != snake->body->next->pos.y)
    {
        node_t *temp = snake->body->next;
        Position prev = snake->body->pos;
        Position next = temp->pos;

        while(temp != NULL)
        {
            temp->pos = prev;
            temp = temp->next;
            prev = next;
            next = (temp != NULL) ? temp->pos : prev;
        }
    }
}

/*
This functions renders the head of the snake.

function: renderSnake
param: body, ptr to body of snake
*/

void renderSnakeHead()
{
    if(snake->body == NULL)
    {
        printf("There is no snake body!\n");
        return;
    }

    snakeRect.x = snake->body->pos.x;
    snakeRect.y = snake->body->pos.y;

    SDL_SetRenderDrawColor(gRenderer, snake->color.r, snake->color.g, snake->color.b, snake->color.a);
    SDL_RenderFillRect(gRenderer, &snakeRect);
}

void renderSnakeBody()
{
    if(snake->body->next == NULL)
        return;

    node_t *temp = snake->body->next;

    while(temp != NULL)
    {
        bodyRect.x = temp->pos.x;
        bodyRect.y = temp->pos.y;

        SDL_SetRenderDrawColor(gRenderer, snake->color.r, snake->color.g, snake->color.b, snake->color.a);
        SDL_RenderFillRect(gRenderer, &bodyRect);

        temp = temp->next;
    }
}

void checkBoundaries()
{

    if(snake->body == NULL)
    {
        printf("There is no snake body!\n");
        return;
    }

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
        case MEDIUM:
        case HARD:
            if(snake->body->pos.x < 0 || snake->body->pos.x > WIDTH || snake->body->pos.y < GRIDOFFSET || snake->body->pos.y > HEIGHT) 
            {
                freeSnake();
                freeFood();
            }
            break;
    }
}

static void freeSnake()
{

    /*deallocate memory for snake body*/
    free(snake->body);

    /*deallocate memory made for snake struct*/
    free(snake);
}

static void freeFood()
{
    /*deallocate memory made for food struct*/
    free(food);
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

static node_t *create_new_body_node(Position pos)
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

static void insertBodyNode(Position newPos)
{
    node_t *temp;

    if(snake->body == NULL)
        return;

    temp = snake->body;

    /*this goes through the linked list till it reaches the last element*/
    while(temp->next != NULL)
    {
        temp = temp->next;
        newPos = temp->pos;
    }
    temp->next = create_new_body_node(newPos);
}

void printBody()
{
    node_t *temp = snake->body;
    while(temp != NULL)
    {
        printf("[%d, %d]->", temp->pos.x, temp->pos.y);
        temp = temp->next;
    }

    printf("NULL\n");
}