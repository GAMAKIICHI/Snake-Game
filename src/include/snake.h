#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <graphics.h>
#include <grid.h>
#include <time.h>
#include <math.h>
#include <gamestate.h>
#include <SDL2/SDL_mixer.h>
#include <audio.h>

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
    SDL_Color color;
} Food;

typedef struct
{
    int size;
    SDL_Color color;
    enum Difficulty difficulty;
}settings;

/*Food Functions*/
void initFood();
void placeFood();
void renderFood();

/*Snake Functions*/
void initSnake();

Position handleKeyEvent(SDL_Event *e);
static Position generateRandomPos(int seed);

void move();
void renderSnakeHead();

static void moveBody();
void renderSnakeBody();

void checkBoundaries();

static void freeSnake();
static void freeFood();

int getScore();
void setColor(SDL_Color selectedColor);

/*Linked List Functions*/
static node_t *create_new_body_node(Position);
static void insertBodyNode(Position newPos);

void printBody();

#endif