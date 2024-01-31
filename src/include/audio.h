#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <graphics.h>

/*Audio*/
bool loadAudio();
void freeAudio();

void playBeep();

#endif

