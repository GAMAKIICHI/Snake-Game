#include "snake.h"

unsigned int lastMoved = 0;

Snake playerSnake = {NULL, {0,0}, 0, MEDIUM};
Food food = {0,0};

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

    if(currentTime - lastMoved >= s->difficulty)
    {
        /*updates head of linked list that stores pos of head of snake*/
        s->body->value.x += s->sVel.x;
        s->body->value.y += s->sVel.y;

        lastMoved = currentTime;
    }

    /*
    This checks whether the snake has a body and whether the head of the snake is in a new grid pos. 
    If it is the positions of the snake will shift down the linked list.
    */
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

void renderSnakeHead(node_t *head)
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
        bodyRect.x = temp->value.x;
        bodyRect.y = temp->value.y;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x0, 0x0, 0xFF);
        SDL_RenderFillRect(gRenderer, &bodyRect);
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

bool isGameOver(Snake s)
{
    /*
    These are the boundaries for each difficulty.
    EASY DIFFICULTY: If you hit the end of the grid you will end up on the opposite of the grid
    MEDIUM/ HARD DIFFICULTY: If you hit the end of the grid the game will end will end.
    */

    switch(s.difficulty)
    {
        case EASY:
            if(s.body->value.x > WIDTH)
                s.body->value.x = 0;
            else if(s.body->value.x < 0)
                s.body->value.x = WIDTH;
            else if(s.body->value.y > HEIGHT)
                s.body->value.y = 0;
            else if(s.body->value.y < 0)
                s.body->value.y = HEIGHT;
            break;
        case MEDIUM:
        case HARD:
            if(s.body->value.x > WIDTH || s.body->value.x < 0 || s.body->value.y > HEIGHT || s.body->value.y < 0)
            {
                freeSnake(s.body);
                return true;
            }
            break;
    }

    return false;
}

/*
This functions allocates space for a new node,
and sets the next last node to null.

function: creat_new_node
param: value, current pos when added to body
returns: node_t
*/

node_t *create_new_node(Position value)
{
    /*allocate memory for new node*/
    node_t *result = malloc(sizeof(node_t));

    result->value = value;
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

void insertNodeAtEnd(node_t *head)
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
        newPos = temp->value;
    }
    temp->next = create_new_node(newPos);
}

/*
This functions shifts all the elements inside
linked list to the right. Starting at the second element

function: shift
param: body, ptr to body of snake
*/

void shift(node_t *body)
{
    if(body == NULL || body->next == NULL)
    {
        return;
    }

    node_t *temp = body;
    Position shiftedPos[1000];
    int i = 0;

    while(temp != NULL)
    {
        shiftedPos[i++] = temp->value;
        temp = temp->next;
    }

    /*temp starts at the second pos in body. We dont want to update the head. Just the body*/
    temp = body->next;
    i = 0;

    while(temp != NULL)
    {
        temp->value = shiftedPos[i++];
        temp = temp->next;
    }
}

void freeSnake(node_t *head)
{
    node_t *tmp;
    tmp = head;
    while(tmp != NULL)
    {
        free(tmp);
        tmp = tmp->next;
    }
}

void printlist(node_t *head)
{
    node_t *temp = head;
    while(temp != NULL)
    {
        printf("[%d, %d]->", temp->value.x, temp->value.y);
        temp = temp->next;
    }

    printf("NULL\n");
}

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

    for(int i = 0; i < 10; i++)
    {
        shift(head);
        head->value = (Position){i,i};
        printlist(head);
    }
}