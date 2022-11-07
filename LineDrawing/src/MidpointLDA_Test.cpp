#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "MidpointLDA.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(640, 480, 5, "Midpoint Line Drawing");

    MidpointLDA mplda;
    MidpointLDAArgs args{ -10, 20, 30, 40 };

    window.SetAlgorithm(mplda, args);
    window.LoopAndDraw(GREEN);

    return 0;
}