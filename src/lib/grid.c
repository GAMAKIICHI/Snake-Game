#include "grid.h"

SDL_Rect gridRect = {(int)NULL,(int)NULL,16,16};

void renderGrid()
{
    for(int row = GRIDOFFSET; row <= HEIGHT; row+=16)
    {
        for(int col = 0; col <= WIDTH; col+=16)
        {
            gridRect.x = col;
            gridRect.y = row;
            SDL_SetRenderDrawColor(gRenderer, getActiveColor().r, getActiveColor().g, getActiveColor().b, getActiveColor().a);
            SDL_RenderDrawRect(gRenderer, &gridRect);
        }
    }
}