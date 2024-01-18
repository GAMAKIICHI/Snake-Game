#include "scene_manager.h"

FontSetting defaultFont = {"fonts/munro.ttf", 64, {0x7f, 0x03, 0xfc, 0xFF}};

void gameScene()
{
    /*update the pos of the snake*/
    move(&playerSnake);
    renderSnakeHead(playerSnake.body);
    renderBody(playerSnake.body);

    /*Check whether the snake head has collided with food*/
    if(checkCollision(snakeRect, foodRect))
    {
        /*Add new body node*/
        insertNodeAtEnd(playerSnake.body);
        placeFood(&food);
        playerSnake.score++;
    }

    // printlist(playerSnake.body);
    renderGrid();
    renderFood(&food);
}

void gameOverScene()
{
    char score[10];
    sprintf(score, "SCORE: %d", 565);

    renderText("Game Over", defaultFont.fontPath, defaultFont.fontSize, defaultFont.color, (WIDTH - gScreenSurface->w) / 2,96);

    renderText(score, defaultFont.fontPath, 48, defaultFont.color, (WIDTH - gScreenSurface->w) / 2,20);
}