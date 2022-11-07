#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "BresenhamCircle.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(640, 480, 5, "Bresenham's Circle Drawing");

    BresenhamCircle bcda;
    BresenhamCircleArgs args{ -20, -30, 50 };

    window.SetAlgorithm(bcda, args);
    window.LoopAndDraw(GREEN);

    return 0;
}