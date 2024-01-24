#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"
#include "graphics.h"
#include "grid.h"

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
    Position pos;
    struct Node *next;
}node_t;

typedef struct
{
    node_t *body;
    Position sVel;
    unsigned int score;
    enum Difficulty difficulty;
    int size;
    SDL_Color color;
} Snake;

typedef struct
{
    Position pos;
    int size;
} Food;

typedef struct
{
    int size;
    SDL_Color color;
    enum Difficulty difficulty;
}settings;

extern unsigned int lastMoved;

/*Food Functions*/
void initFood();
void placeFood();
void renderFood();

/*Snake Functions*/
void initSnake();

Position handleKeyEvent(SDL_Event *);
void move();
void renderSnakeHead();

void checkBoundaries();

int getScore();

/*Linked List Functions*/
node_t *create_new_body_node(Position);
void insertBodyNode(node_t *);

void printlist(node_t *);
void testBody();

#endif