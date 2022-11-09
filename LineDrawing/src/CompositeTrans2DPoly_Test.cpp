#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "CompositeTrans2DPoly.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(800, 650, 2, "Composite Transform on a 2D Polygon");

    Composite2DPoly r2DArgs;
    Composite2DPolyArgs args{
        { {200, 50}, {250, 100}, {200, 150},
        {100, 150}, {50, 100}, {100, 50} },
        {50, 50},
        {0, 0},
        85
    };

    window.SetAlgorithm(r2DArgs, args);
    window.LoopAndDraw(GREEN);

    return 0;
}