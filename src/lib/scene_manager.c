#include "scene_manager.h"

FontSetting defaultFont = {"fonts/munro.ttf", 64, {0x1C, 0xFC, 0x3, 0xFF}};
ButtonSettings defaultButton = {175, 64, 32, {0x1C, 0xFC, 0x3, 0xFF}, {0x93, 0xFF, 0x73, 0xFF}};

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

void mainMenuScene(SDL_Keycode btn)
{
    renderText("SNAKE", defaultFont.fontPath, defaultFont.fontSize, defaultFont.color, 0, 20);

    renderText("CONTROLS: ARROW KEYS", defaultFont.fontPath, 32, defaultFont.color, 0, 120);

    Button startBtn = {"START", defaultButton.width, defaultButton.height, 0, 200, defaultButton.fontSize, false, defaultButton.color, defaultButton.color};
    Button settingsBtn = {"SETTINGS", defaultButton.width, defaultButton.height, 0, 280, defaultButton.fontSize, false, defaultButton.color, defaultButton.color};

    if(btn == SDLK_UP)
        startBtn.color = (SDL_Color){0xFF,0XFF,0XFF,0XFF};
    else if(btn == SDLK_DOWN)  
        settingsBtn.color = settingsBtn.focus;

    renderButton(startBtn);
    renderButton(settingsBtn);
}

void gameOverScene()
{
    char score[10];

    /*Convert score from int to char*/
    sprintf(score, "SCORE: %d", playerSnake.score);

    renderText("GAME OVER", defaultFont.fontPath, defaultFont.fontSize, defaultFont.color, 0,20);

    renderText(score, defaultFont.fontPath, 48, defaultFont.color, 0,120);

    Button playAgainBtn = {"PLAY AGAIN?", defaultButton.width, defaultButton.height, 0, 200, defaultButton.fontSize, false, defaultButton.color, defaultButton.color};
    Button exitBtn = {"EXIT", defaultButton.width, defaultButton.height, 0, 280, defaultButton.fontSize, false, defaultButton.color, defaultButton.color};
    
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