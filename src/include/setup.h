#ifndef SETUP_H
#define SETUP_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <graphics.h>
#include <stdio.h>

/*Starts up SDL and creates window*/
bool init();

/*Frees media and shuts down SDL*/
void closeWindow();

#endif