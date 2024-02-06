#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL_pixels.h>
#include <stdbool.h>

typedef struct
{
    char fontPath[1000];
    int fontSize;
}FontSetting;

typedef struct 
{
    int width;
    int height;
    int fontSize;
    SDL_Color *color;
    SDL_Color *focus;

}ButtonSettings;

typedef struct
{
    int fontSize;
    SDL_Color *color;
    SDL_Color *focus;
}SliderSettings;

extern SDL_Color colors[];

extern FontSetting fontSettings;
extern ButtonSettings buttonSettings;
extern SliderSettings defaultSliderSettings;

int getSize();

SDL_Color getActiveColor();
SDL_Color getFocusColor();
void setActiveColor(SDL_Color newColor);

int getSound();
void incSound();
void decSound();

#endif