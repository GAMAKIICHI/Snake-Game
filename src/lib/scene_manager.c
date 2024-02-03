#include "scene_manager.h"

static Button startBtn = {"START", 0, 200, true, false, &buttonSettings};
static Button settingsBtn = {"SETTINGS", 0, 280, true, false, &buttonSettings};

static Button playAgainBtn = {"PLAY AGAIN?", 0, 200, true, false, &buttonSettings};
static Button exitBtn = {"EXIT", 0, 280, true, false, &buttonSettings};

static Slider soundBar = {155, false, &defaultSliderSettings};
static Slider colorBar = {215, false, &defaultSliderSettings};
static Slider difficultySlider = {95, false, &defaultSliderSettings};

static char score[10];
static char difficulty[20] = "EASY";

/*This control which button is in focus on settings scene*/
static int selectedButton = 0;

/*This controls which color is selected on color bar*/
static int selectedColorBtn = 0;

/*This controls which difficulty is selected on slider*/
static int selectedDifficultyBtn = 0;

void gameScene()
{
    /*Convert score from int to char*/
    sprintf(score, "SCORE: %d", getScore());

    renderText(score, fontSettings.fontPath, 32, getActiveColor(), -184, 2);

    renderGrid();

    move();
    checkBoundaries();

    renderSnakeHead();
    renderSnakeBody();

    placeFood();
    renderFood();
}

void mainMenuScene()
{
    renderText("SNAKE", fontSettings.fontPath, fontSettings.fontSize, getActiveColor(), 0, 20);

    renderText("CONTROLS: ARROW KEYS", fontSettings.fontPath, 32, getActiveColor(), 0, 120);

    if(selectedButton == 0)
    {
        startBtn.isFocus = true;
        settingsBtn.isFocus = false;
    }
    else if(selectedButton == 1)
    {
        settingsBtn.isFocus = true;
        startBtn.isFocus = false;
    }
    else if(selectedButton == -1 && startBtn.isFocus)
    {
        resetSelectedButton();
        setGameState(GAME);
    }
    else if(selectedButton == -1 && settingsBtn.isFocus)
    {
        resetSelectedButton();
        setGameState(SETTINGS);
    }

    renderButton(startBtn);
    renderButton(settingsBtn);
}

void gameOverScene()
{
    renderText("GAME OVER", fontSettings.fontPath, fontSettings.fontSize, getActiveColor(), 0,20);

    renderText(score, fontSettings.fontPath, 48, getActiveColor(), 0,120);

    if(selectedButton == 0)
    {
        playAgainBtn.isFocus = true;
        exitBtn.isFocus = false;
    }
    else if(selectedButton == 1)
    {
        exitBtn.isFocus = true;
        playAgainBtn.isFocus = false;
    }
    else if(selectedButton == -1 && playAgainBtn.isFocus)
    {
        initSnake();
        initFood();
        resetSelectedButton();
        setGameState(GAME);
    }
    else if(selectedButton == -1 && exitBtn.isFocus)
    {
        resetSelectedButton();
        initSnake();
        initFood();
        setGameState(MAINMENU);
    }

    renderButton(playAgainBtn);
    renderButton(exitBtn);
}

void settingsScene()
{
    renderText("SETTINGS", fontSettings.fontPath, fontSettings.fontSize, getActiveColor(), 0, 20);

    /*Update difficulty text*/
    if(getDifficulty() == EASY)
    {
        snprintf(difficulty, 10, "EASY");
    }
    else if(getDifficulty() == MEDIUM)
    {
        snprintf(difficulty, 10, "MEDIUM");
    }
    else if(getDifficulty() == HARD)
    {
        snprintf(difficulty, 10, "HARD");
    }


    // if(selectedButton == 0)
    // {
    //     defaultDifficultySlider.isFocus = true;
    //     defaultSoundBar.isFocus = false;
    //     defaultColorBar.isFocus = false;
    //     exitBtn.isFocus = false;
    // }
    // else if(selectedButton == 1)
    // {
    //     defaultSoundBar.isFocus = true;
    //     defaultDifficultySlider.isFocus = false;
    //     defaultColorBar.isFocus = false;
    //     exitBtn.isFocus = false;
    // }
    // else if(selectedButton == 2)
    // {
    //     defaultColorBar.isFocus = true;
    //     defaultDifficultySlider.isFocus = false;
    //     defaultSoundBar.isFocus = false;
    //     exitBtn.isFocus = false;
    // }
    // else if(selectedButton == 3)
    // {
    //     exitBtn.isFocus = true;
    //     defaultDifficultySlider.isFocus = false;
    //     defaultColorBar.isFocus = false;
    //     defaultSoundBar.isFocus = false;
    // }
    // else if(selectedButton == -1 && exitBtn.isFocus)
    // {
    //     /*This applies settings*/
    //     initSnake();
    //     initFood();
    //     setGameState(MAINMENU);
    // }

    // if(defaultColorBar.isFocus)
    // {
    //     setActiveColor(colors[selectedColorBtn]);
    //     setColors();
    // }

    renderDifficultySlider(difficultySlider);
    renderSoundBar(5, soundBar);
    renderColorBar(colorBar);
    renderButton(exitBtn);
}

void setColors()
{
    // activeColor = getActiveColor();
    // startBtn.color = getActiveColor();
    // settingsBtn.color = getActiveColor();
    // playAgainBtn.color = getActiveColor();
    // exitBtn.color = getActiveColor();
    // defaultSoundBar.color = getActiveColor();
    // defaultColorBar.color = getActiveColor();
    
    setColor(getActiveColor());
    setGridColor(getActiveColor());
}

void resetSelectedButton()
{
    selectedButton = 0;
}

void handleButtonEvents(SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0) /*e->key.repeat == 0 ensures a key wont be repeatedly detected if held down*/
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_UP:
                if((getGameState() == MAINMENU || getGameState() == GAMEOVER || getGameState() == SETTINGS ) && selectedButton > 0)
                {
                    selectedButton--;
                }
                playBeep();
                break;
            case SDLK_DOWN:
                if((getGameState() == MAINMENU || getGameState() == GAMEOVER) && selectedButton < 1)
                {
                    selectedButton++;
                }
                else if(getGameState() == SETTINGS && selectedButton < 3)
                {
                    selectedButton++;
                }
                playBeep();
                break;
            case SDLK_RIGHT:
                if(getGameState() == SETTINGS) /*Increases Volume Level*/
                {

                    // /*Adjust Difficulty*/
                    // if(defaultDifficultySlider.isFocus && selectedDifficultyBtn < 2)
                    // {
                    //     ++selectedDifficultyBtn;
                    //     setDifficulty(selectedDifficultyBtn);
                    // }

                    // /*Adjust Color*/
                    // if(defaultColorBar.isFocus && selectedColorBtn < sizeof(colors) / sizeof(colors[0]) - 1)
                    // {
                    //     selectedColorBtn++;
                    // }
                    // else if(defaultSoundBar.isFocus && getSound() < 5)
                    // {
                    //     incSound();
                    // }
                    
                    /*Adjusts volume*/
                    if(getSound() == 0)
                    {
                        Mix_Volume(-1, getSound());
                    }
                    else
                    {   
                        Mix_Volume(-1, getSound() * 15);
                    }

                    playBeep();
                }
                break;
            case SDLK_LEFT: 
                if(getGameState() == SETTINGS) /*Decreases Volume Level*/
                {
                    // /*Adjust Difficulty*/
                    // if(defaultDifficultySlider.isFocus && selectedDifficultyBtn > 0)
                    // {
                    //     --selectedDifficultyBtn;
                    //     setDifficulty(selectedDifficultyBtn);
                    // }

                    // /*Adjust Color*/
                    // if(defaultColorBar.isFocus && selectedColorBtn > 0)
                    // {
                    //     selectedColorBtn--;
                    // }
                    // else if(defaultSoundBar.isFocus && getSound() > 0)
                    // {
                    //     decSound();
                    // }

                    /*Adjusts volume*/
                    if(getSound() == 0)
                    {
                        Mix_Volume(-1, getSound());
                    }
                    else
                    {   
                        Mix_Volume(-1, getSound() * 15);
                    }
                    playBeep();
                }
                break;
            case SDLK_RETURN:
                selectedButton = -1;
                break;
        }
    }
}