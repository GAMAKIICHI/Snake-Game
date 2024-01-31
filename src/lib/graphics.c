#include "graphics.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Renderer *gRenderer = NULL;

SDL_Rect foodRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect snakeRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect bodyRect = {(int)NULL, (int)NULL, 16,16};

static unsigned int sound = 5;
static SDL_Rect soundRect = {(int)NULL, (int)NULL, 16,32};
static SDL_Rect colorRect = {(int)NULL, (int)NULL, 16,32};

/*Colors: green, red, blue, purple, orange*/
SDL_Color colors[] = {{0x1C, 0xFC, 0x3, 0xFF}, {0xFC,0x03,0x03,0xFF}, {0x0b,0x03,0xFC,0xFF}, {0xFC,0x03,0xF4,0xFF}, {0xFC,0x80,0x03,0xFF}};

SDL_Color selectedColor = {0x1C, 0xFC, 0x3, 0xFF};

/*
This function renders text to the window. 
Text will be rendered to the center of the screen on the x axis by default. 
You can offset the text by using the posX param. negative values will make the 
text render to the left. Positive values will render the text to the right.

function: renderText
param: str, text that will be rendered
       fontPath, Path to font to font style that will be rendered
       fontSize, size of font
       color, color of text
       posX, 
*/

void renderText(char str[], char fontPath[], int fontSize, SDL_Color color, int posX, int posY)
{
    SDL_Texture *tTexture = NULL;
    SDL_Surface *tSurface = NULL;
    TTF_Font *gfont = NULL;

    gfont = TTF_OpenFont(fontPath, fontSize);

    if(gfont == NULL)
    {
        printf("unable in initialize font! TTF_Error: %s\n", TTF_GetError());
    }

    tSurface = TTF_RenderText_Solid(gfont, str, color);

    if(tSurface == NULL)
    {
        printf("unable to render text surface! SDL_Error: %s\n", SDL_GetError());
    }

    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    if(tTexture == NULL)
    {
        printf("unable to create texuture from surface! SDL_Error: %s\n", SDL_GetError());
    }

    SDL_Rect destinationRect = {centerSurface(tSurface) + posX, posY, tSurface->w, tSurface->h};
    SDL_RenderCopy(gRenderer, tTexture, NULL, &destinationRect);

    TTF_CloseFont(gfont);
    SDL_DestroyTexture(tTexture);
    SDL_FreeSurface(tSurface);
}

void renderButton(Button btn)
{
    SDL_Rect button = {(WIDTH - btn.width) / 2 + btn.posX, btn.posY, btn.width, btn.height};

    /*This centers the text on the y axis of the button*/
    int centerTextY = btn.posY + (btn.height - btn.fontSize) / 2;

    /*this changes the color of the button if its focused*/
    if(btn.isFocus)
    {
        SDL_SetRenderDrawColor(gRenderer, btn.focus.r, btn.focus.g, btn.focus.b, btn.focus.a);
        renderText(btn.str, "assets/fonts/munro.ttf", btn.fontSize, btn.focus, btn.posX, centerTextY);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer, btn.color.r, btn.color.g, btn.color.b, btn.color.a);
        renderText(btn.str, "assets/fonts/munro.ttf", btn.fontSize, btn.color, btn.posX, centerTextY);
    }
    
    SDL_RenderDrawRect(gRenderer, &button);
}

int centerSurface(SDL_Surface *surface)
{
    return (WIDTH - surface->w) / 2;
}

void renderSoundBar(char fontPath[], int numSound, int xOffset, int posY, SDL_Color color, SDL_Color focus, bool isFocus)
{
    int fontSize = 48;

    if(isFocus)
        renderText("SOUND:", fontPath, fontSize, focus, xOffset, posY);
    else if(!isFocus)
        renderText("SOUND:", fontPath, fontSize, color, xOffset, posY);

    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

    soundRect.y = posY + (fontSize-soundRect.h);
    soundRect.x = (WIDTH / 2.2);

    for(int i = 1; i <= numSound; i++)
    {
        if(i <= sound)
        {
            SDL_RenderFillRect(gRenderer, &soundRect);
        }
        else
        {
            SDL_RenderDrawRect(gRenderer, &soundRect);
        }

        soundRect.x = soundRect.x + soundRect.w + soundRect.w / 2;
    }

}

void incSound()
{
    sound++;
}

void decSound()
{
    sound--;
}

int getSound()
{
    return sound;
}

void renderColorBar(char fontPath[], int xOffset, int posY, SDL_Color color, SDL_Color focus, SDL_Color *selectedColor, bool isFocus)
{
    int fontSize = 48;
    int w = colorRect.w;
    int h = colorRect.h;

    if(isFocus)
        renderText("COLOR:", fontPath, fontSize, focus, xOffset, posY);
    else if(!isFocus)
        renderText("COLOR:", fontPath, fontSize, color, xOffset, posY);

    colorRect.y = posY + (fontSize-colorRect.h);
    colorRect.x = (WIDTH / 2.2);

    for(int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++)
    {
        SDL_SetRenderDrawColor(gRenderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        SDL_RenderFillRect(gRenderer, &colorRect);

        /*Draws a white outline of current color thats selected*/
        if(colors[i].r == selectedColor->r && colors[i].g == selectedColor->g && colors[i].b == selectedColor->b && colors[i].a == selectedColor->a)
        {
            SDL_SetRenderDrawColor(gRenderer, focus.r, focus.g, focus.b, focus.a);
            colorRect.w = colorRect.w + 1;
            colorRect.h = colorRect.h + 1;
            SDL_RenderDrawRect(gRenderer, &colorRect);
            colorRect.w = w;
            colorRect.h = h;
        }
        colorRect.x = colorRect.x + colorRect.w + colorRect.w / 2;
    }
}