#ifndef GRID_H
#define GRID_H

#include "graphics.h"
#include "settings.h"

/*This offsets the grid by the height of the score text + offset of text*/
#define GRIDOFFSET 32

void renderGrid();

void setGridColor(SDL_Color newColor);

#endif