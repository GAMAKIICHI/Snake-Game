#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"

#define WIDTH 480
#define HEIGHT 368

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface; 
extern SDL_Renderer *gRenderer;
extern SDL_Texture *gTexture;

extern SDL_Rect gridRect;
extern SDL_Rect foodRect;
extern SDL_Rect snakeRect;
extern SDL_Rect bodyRect;

#endif