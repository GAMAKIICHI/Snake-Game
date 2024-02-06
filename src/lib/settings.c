#include <settings.h>

static SDL_Color activeColor = {0x1C, 0xFC, 0x3, 0xFF};
static SDL_Color focusColor = {0xFF,0XFF,0XFF,0XFF};

/*Colors: green, red, blue, purple, orange*/
SDL_Color colors[] = {{0x1C, 0xFC, 0x3, 0xFF}, {0xFC,0x03,0x03,0xFF}, {0x0b,0x03,0xFC,0xFF}, {0xFC,0x03,0xF4,0xFF}, {0xFC,0x80,0x03,0xFF}};

static unsigned int sound = 5;
static unsigned int size = 16;

FontSetting fontSettings = {"assets/fonts/munro.ttf", 64};
ButtonSettings buttonSettings = {175, 64, 32, &activeColor, &focusColor};
SliderSettings defaultSliderSettings = {48, &activeColor, &focusColor};

int getSize()
{
    return size;
}

SDL_Color getActiveColor()
{
    return activeColor;
}

SDL_Color getFocusColor()
{
    return focusColor;
}

void setActiveColor(SDL_Color newColor)
{
    activeColor = newColor;
}

int getSound()
{
    return sound;
}

void incSound()
{
    sound++;
}

void decSound()
{
    sound--;
}