#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"
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
}Button;

void renderText(char str[], char fontPath[], int fontSize, SDL_Color color, int posX, int posY);
void renderButton(Button btn);
int centerSurface(SDL_Surface *surface);
void clear();

#endif