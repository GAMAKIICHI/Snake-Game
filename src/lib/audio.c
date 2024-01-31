#include <audio.h>

/*Beep sound effect*/
static Mix_Chunk *gBeep = NULL;

bool loadAudio()
{
    /*Load success flag*/
    bool success = true;

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }


    /*Load beep sound effect*/
    gBeep = Mix_LoadWAV("assets/sounds/one_beep-99630.mp3");
    if(gBeep == NULL)
    {
        printf("Unable to load beep sound effect! SDL_ERROR: %s\n", Mix_GetError());
        success = false;
    }
    else
    {
        Mix_Volume(-1, getSound() * 15);
    }

    return success;
}

void freeAudio()
{
    Mix_FreeChunk(gBeep);
    gBeep = NULL;
    Mix_Quit();
}

void playBeep()
{
    Mix_PlayChannel(-1, gBeep, 0);
}