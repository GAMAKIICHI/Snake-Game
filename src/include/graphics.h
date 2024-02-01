#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

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
    int width;
    int height;
    int posX;
    int posY;
    int fontSize;
    bool isFocus;
    SDL_Color color;
    SDL_Color focus;
    bool outline;
}Button;

void initColors();

void renderText(char str[], char fontPath[], int fontSize, SDL_Color color, int posX, int posY);
void renderButton(Button btn);
int centerSurface(SDL_Surface *surface);

void renderDifficultySlider(char fontPath[], char difficulty[], int xOffset, int posY, SDL_Color color, SDL_Color focus, bool isFocus);

void renderSoundBar(char fontPath[], int numSound, int xOffset, int posY, SDL_Color color, SDL_Color focus, bool isFocus);
void incSound();
void decSound();
int getSound();

void renderColorBar(char fontPath[], int xOffset, int posY, SDL_Color color, SDL_Color focus, SDL_Color *selectedColor, bool isFocus);

#endif