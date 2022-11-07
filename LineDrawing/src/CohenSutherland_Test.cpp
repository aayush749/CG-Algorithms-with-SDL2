#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "CohenSutherland.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(640, 480, 2, "Cohen Sutherland Line Clipping");

    CohenSutherland cs;
    CohenSutherlandArgs args{ -10, 50, 30, 80, -30, 20, 10, 60 };

    window.SetAlgorithm(cs, args);
    window.LoopAndDraw(GREEN);

    return 0;
}