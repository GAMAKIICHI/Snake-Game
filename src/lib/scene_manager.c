#include "scene_manager.h"

SDL_Color selectedColor = {0x1C, 0xFC, 0x3, 0xFF};
static FontSetting defaultFont = {"fonts/munro.ttf", 64, {0x1C, 0xFC, 0x3, 0xFF}};

static Button startBtn = {"START", 175, 64, 0, 200, 32, true, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};
static Button settingsBtn = {"SETTINGS", 175, 64, 0, 280, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};

static Button playAgainBtn = {"PLAY AGAIN?", 175, 64, 0, 200, 32, true, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};
static Button exitBtn = {"EXIT", 175, 64, 0, 280, 32, false, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}};

static barSettings defaultSoundBar = {"fonts/munro.ttf", 5, -96, 120, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}, true};
static barSettings defaultColorBar = {"fonts/munro.ttf", (int)NULL, -96, 192, {0x1C, 0xFC, 0x3, 0xFF}, {0xFF,0XFF,0XFF,0XFF}, false};

static char score[10];

/*These control which button is in focus on settings scene*/
static unsigned int selectedButton = 0;

void gameScene()
{

    /*Convert score from int to char*/
    sprintf(score, "SCORE: %d", getScore());

    renderText(score, defaultFont.fontPath, 32, defaultFont.color, -184, 2);

    renderGrid();

    move();
    checkBoundaries();

    renderSnakeHead();
    renderSnakeBody();

    placeFood();
    renderFood();
}

void mainMenuScene(SDL_Keycode btn)
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
    else if(btn == SDLK_RETURN && startBtn.isFocus)
    {
        setGameState(GAME);
    }
    else if(btn == SDLK_RETURN && settingsBtn.isFocus)
    {
        setGameState(SETTINGS);
    }

    renderButton(startBtn);
    renderButton(settingsBtn);
}

void gameOverScene(SDL_Keycode btn)
{
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
    else if(btn == SDLK_RETURN && playAgainBtn.isFocus)
    {
        initSnake();
        initFood();
        setGameState(GAME);
    }
    else if(btn == SDLK_RETURN && exitBtn.isFocus)
    {
        quit = true;
    }

    renderButton(playAgainBtn);
    renderButton(exitBtn);
}

void settingsScene(SDL_Keycode btn)
{
    renderText("SETTINGS", defaultFont.fontPath, defaultFont.fontSize, defaultFont.color, 0, 20);

    if(btn == SDLK_UP && selectedButton >= 0)
    {
        selectedButton--;
    }
    else if(btn == SDLK_DOWN && selectedButton <= 2)
    {
        selectedButton++;
    }

    if(selectedButton == 0)
    {
        defaultSoundBar.isFocus = true;
        defaultColorBar.isFocus = false;
        exitBtn.isFocus = false;
    }
    else if(selectedButton == 1)
    {
        defaultColorBar.isFocus = true;
        defaultSoundBar.isFocus = false;
        exitBtn.isFocus = false;
    }
    else if(selectedButton == 2)
    {
        exitBtn.isFocus = true;
        defaultColorBar.isFocus = false;
        defaultSoundBar.isFocus = false;
    }

    renderSoundBar(defaultSoundBar.fontPath, defaultSoundBar.numSound, defaultSoundBar.xOffset, defaultSoundBar.posY, defaultSoundBar.color, defaultSoundBar.focus, defaultSoundBar.isFocus);
    renderColorBar(defaultColorBar.fontPath, defaultColorBar.xOffset, defaultColorBar.posY, defaultColorBar.color, defaultColorBar.focus, &selectedColor, defaultColorBar.isFocus);
    renderButton(exitBtn);
}

void setColors()
{
    defaultFont.color = selectedColor;
    startBtn.color = selectedColor;
    settingsBtn.color = selectedColor;
    playAgainBtn.color = selectedColor;
    exitBtn.color = selectedColor;
    defaultSoundBar.color = selectedColor;
    defaultColorBar.color = selectedColor;

    setColor(selectedColor);
}

SDL_Keycode handleButtonEvents(SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN)
    {
        return e->key.keysym.sym;
    }
}