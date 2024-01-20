#include "graphics.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Renderer *gRenderer = NULL;

SDL_Rect foodRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect snakeRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect bodyRect = {(int)NULL, (int)NULL, 16,16};

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
        renderText(btn.str, "fonts/munro.ttf", btn.fontSize, btn.focus, btn.posX, centerTextY);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer, btn.color.r, btn.color.g, btn.color.b, btn.color.a);
        renderText(btn.str, "fonts/munro.ttf", btn.fontSize, btn.color, btn.posX, centerTextY);
    }
    
    SDL_RenderDrawRect(gRenderer, &button);
}

int centerSurface(SDL_Surface *surface)
{
    return (WIDTH - surface->w) / 2;
}

void clear()
{
    /*Get rid of old surface*/
    SDL_FreeSurface(gScreenSurface);
}