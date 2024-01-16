#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"
#include "graphics.h"

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

typedef struct {
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
    enum Difficulty difficulty;
} Snake;

typedef struct
{
    Position pos;
} Food;

extern unsigned int lastMoved;
extern Snake playerSnake;
extern Food food;

void handleKeyEvent(SDL_Event *, Snake *);
void move(Snake *);
void renderSnakeHead(node_t *);
void renderBody(node_t *);

bool checkCollision(SDL_Rect, SDL_Rect);
bool isInNewGrid(Position , Position);

void placeFood(Food *);
void renderFood(Food *);

bool isGameOver(Snake);

node_t *create_new_node(Position);
void insertNodeAtEnd(node_t *);
void shift(node_t *);
void freeSnake(node_t *);

void printlist(node_t *);
void testBody();

#endif