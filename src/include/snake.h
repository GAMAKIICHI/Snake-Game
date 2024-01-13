#include <stdbool.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"
#include "graphics.h"
#include "position.h"
#include "linkedlist.h"

#ifndef SNAKE_H
#define SNAKE_H

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

extern unsigned int lastMoved;

void handleKeyEvent(SDL_Event *, Snake *);
void move(Snake *);
void renderSnake(node_t *);
void renderBody(node_t *);

bool checkCollision(SDL_Rect, SDL_Rect);
bool isInNewGrid(Position , Position);

void placeFood(Food *);
void renderFood(Food *);

#endif