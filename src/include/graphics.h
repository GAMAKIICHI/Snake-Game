#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <settings.h>

#define WIDTH 480
#define HEIGHT 368

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

extern SDL_Rect gridRect;
extern SDL_Rect foodRect;
extern SDL_Rect snakeRect;
extern SDL_Rect bodyRect;

extern SDL_Color colors[5];

extern SDL_Color selectedColor;

typedef struct 
{
    char str[1000];
    int posX;
    int posY;
    bool outline;
    bool isFocus;
    ButtonSettings *defaultSettings;
}Button;

typedef struct
{
    int xOffset;
    int posY;
    bool isFocus;
    SliderSettings *defaultSliderSettings;
}Slider;

void initColors();

void renderText(char str[], char fontPath[], int fontSize, SDL_Color color, int posX, int posY);
void renderButton(Button btn);
static int centerSurface(SDL_Surface *surface);

void renderDifficultySlider(Slider sldr, char currentDifficulty[]);

void renderSoundBar(int numBars, Slider sldr);

void renderColorBar(Slider sldr);

#endif