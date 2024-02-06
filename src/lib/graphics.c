#include "graphics.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; 
SDL_Renderer *gRenderer = NULL;

SDL_Rect foodRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect snakeRect = {(int)NULL, (int)NULL, 16,16};
SDL_Rect bodyRect = {(int)NULL, (int)NULL, 16,16};

static SDL_Rect soundRect = {(int)NULL, (int)NULL, 16,32};
static SDL_Rect colorRect = {(int)NULL, (int)NULL, 16,32};

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
    SDL_Rect button = {(WIDTH - btn.defaultSettings->width) / 2 + btn.posX, btn.posY, btn.defaultSettings->width, btn.defaultSettings->height};
    
    /*This centers the text on the y axis of the button*/
    int centerTextY = btn.posY + (btn.defaultSettings->height - btn.defaultSettings->fontSize) / 2;

    /*this changes the color of the button if its focused*/
    if(btn.isFocus)
    {
        SDL_SetRenderDrawColor(gRenderer, btn.defaultSettings->focus->r, btn.defaultSettings->focus->g, btn.defaultSettings->focus->b, btn.defaultSettings->focus->a);
        renderText(btn.str, fontSettings.fontPath, btn.defaultSettings->fontSize, *btn.defaultSettings->focus, btn.posX, centerTextY);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer, btn.defaultSettings->color->r, btn.defaultSettings->color->g, btn.defaultSettings->color->b, btn.defaultSettings->color->a);
        renderText(btn.str, fontSettings.fontPath, btn.defaultSettings->fontSize, *btn.defaultSettings->color, btn.posX, centerTextY);
    }
    
    if(btn.outline)
    {
        SDL_RenderDrawRect(gRenderer, &button);
    }
}

static int centerSurface(SDL_Surface *surface)
{
    return (WIDTH - surface->w) / 2;
}

void renderDifficultySlider(Slider sldr, char currentDifficulty[])
{
    renderText("DIFFICULTY:", fontSettings.fontPath, sldr.defaultSliderSettings->fontSize, (sldr.isFocus) ? *sldr.defaultSliderSettings->focus : *sldr.defaultSliderSettings->color, sldr.xOffset, sldr.posY);
    
    renderText(currentDifficulty, fontSettings.fontPath, sldr.defaultSliderSettings->fontSize, *sldr.defaultSliderSettings->color, sldr.xOffset + 168, sldr.posY);
}

void renderSoundBar(int numBars, Slider sldr)
{
    renderText("SOUND:", fontSettings.fontPath, sldr.defaultSliderSettings->fontSize, (sldr.isFocus) ? *sldr.defaultSliderSettings->focus : *sldr.defaultSliderSettings->color, sldr.xOffset, sldr.posY);

    SDL_SetRenderDrawColor(gRenderer, sldr.defaultSliderSettings->color->r, sldr.defaultSliderSettings->color->g, sldr.defaultSliderSettings->color->b, sldr.defaultSliderSettings->color->a);

    soundRect.y = sldr.posY + (sldr.defaultSliderSettings->fontSize-soundRect.h);
    soundRect.x = (WIDTH / 2);

    for(int i = 1; i <= numBars; i++)
    {
        if(i <= getSound())
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

void renderColorBar(Slider sldr)
{
    renderText("COLOR: ", fontSettings.fontPath, sldr.defaultSliderSettings->fontSize, (sldr.isFocus) ? *sldr.defaultSliderSettings->focus : *sldr.defaultSliderSettings->color, sldr.xOffset, sldr.posY);

    colorRect.y = sldr.posY + (sldr.defaultSliderSettings->fontSize-colorRect.h);
    colorRect.x = (WIDTH / 2);

    for(int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++)
    {
        SDL_SetRenderDrawColor(gRenderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        SDL_RenderFillRect(gRenderer, &colorRect);

        /*Draws a white outline of current color thats selected*/
        if(colors[i].r == getActiveColor().r && colors[i].g == getActiveColor().g && colors[i].b == getActiveColor().b)
        {
            SDL_SetRenderDrawColor(gRenderer, getFocusColor().r, getFocusColor().g, getFocusColor().b, getFocusColor().a);
            SDL_RenderDrawRect(gRenderer, &colorRect);
        }
        colorRect.x = colorRect.x + colorRect.w + colorRect.w / 2;
    }
}