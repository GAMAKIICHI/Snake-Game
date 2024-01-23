#include "scene_manager.h"

static FontSetting defaultFont = {"fonts/munro.ttf", 64, {0x1C, 0xFC, 0x3, 0xFF}};

static Button startBtn = {"START", 175, 64, 0, 200, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};
static Button settingsBtn = {"SETTINGS", 175, 64, 0, 280, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};

static Button playAgainBtn = {"PLAY AGAIN?", 175, 64, 0, 200, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};
static Button exitBtn = {"EXIT", 175, 64, 0, 280, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};

void gameScene()
{

    renderGrid();

    renderSnakeHead();

    placeFood();
    renderFood();
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
    sprintf(score, "SCORE: %d", getScore());

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
        return e->key.keysym.sym;
    }
}