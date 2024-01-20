#include "scene_manager.h"

static FontSetting defaultFont = {"fonts/munro.ttf", 64, {0x1C, 0xFC, 0x3, 0xFF}};

static Button startBtn = {"START", 175, 64, 0, 200, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};
static Button settingsBtn = {"SETTINGS", 175, 64, 0, 280, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};

static Button playAgainBtn = {"PLAY AGAIN?", 175, 64, 0, 200, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};
static Button exitBtn = {"EXIT", 175, 64, 0, 280, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};

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

int mainMenuScene(SDL_Keycode btn)
{
    renderText("SNAKE", defaultFont.fontPath, defaultFont.fontSize, defaultFont.color, 0, 20);

    renderText("CONTROLS: ARROW KEYS", defaultFont.fontPath, 32, defaultFont.color, 0, 120);

    if(btn == SDLK_UP)
    {
        startBtn.isFocus = true;
        settingsBtn.isFocus = false;
    }
    else if(btn == SDLK_DOWN) 
    {
        settingsBtn.isFocus = true;
        startBtn.isFocus = false;
    } 
        
    renderButton(startBtn);
    renderButton(settingsBtn);
}

int gameOverScene(SDL_Keycode btn)
{
    char score[10];

    /*Convert score from int to char*/
    sprintf(score, "SCORE: %d", playerSnake.score);

    renderText("GAME OVER", defaultFont.fontPath, defaultFont.fontSize, defaultFont.color, 0,20);

    renderText(score, defaultFont.fontPath, 48, defaultFont.color, 0,120);
    
    if(btn == SDLK_UP)
    {
        playAgainBtn.isFocus = true;
        exitBtn.isFocus = false;
    }
    else if(btn == SDLK_DOWN) 
    {
        exitBtn.isFocus = true;
        playAgainBtn.isFocus = false;
    } 

    renderButton(playAgainBtn);
    renderButton(exitBtn);
}

SDL_Keycode handleButtonEvents(SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP:
                return SDLK_UP;
                break;
            case SDLK_DOWN:
                return SDLK_DOWN;
                break;
            case SDLK_RIGHT:
                return SDLK_RIGHT;
                break;
            case SDLK_LEFT:
                return SDLK_LEFT;
                break;
            default:
                return (SDL_KeyCode) NULL;
                break;
        }
    }
}