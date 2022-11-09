#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "Trans2DPoly.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(640, 480, 2, "Translating 2D Polygon");

    Trans2DPoly t2DArgs;
    Trans2DPolyArgs args{ 
        { {200, 50}, {250, 100}, {200, 150},
        {100, 150}, {50, 100}, {100, 50} }
    };

    window.SetAlgorithm(t2DArgs, args);
    window.LoopAndDraw(GREEN);

    return 0;
}