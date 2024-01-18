#include "graphics.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;

SDL_Rect foodRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect snakeRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect bodyRect = {(int)NULL, (int)NULL, 16,16};

void renderText(char str[], char fontPath[], int fontSize, SDL_Color color, int posX, int posY)
{
    TTF_Font *gfont = NULL;
    gfont = TTF_OpenFont(fontPath, fontSize);

    SDL_Rect destinationRect = {posX, posY, gScreenSurface->w, gScreenSurface->h};
    SDL_RenderCopy(gRenderer, gTexture, NULL, &destinationRect);

    if(gfont == NULL)
    {
        printf("unable in initialize font! TTF_Error: %s\n", TTF_GetError());
    }

    gScreenSurface = TTF_RenderText_Solid(gfont, str, color);

    if(gScreenSurface == NULL)
    {
        printf("unable to render text surface! SDL_Error: %s\n", SDL_GetError());
    }

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

    if(gTexture == NULL)
    {
        printf("unable to create texuture from surface! SDL_Error: %s\n", SDL_GetError());
    }

    TTF_CloseFont(gfont);
}

void freeSurface()
{
    /*Get rid of old surface*/
    SDL_FreeSurface(gScreenSurface);
}