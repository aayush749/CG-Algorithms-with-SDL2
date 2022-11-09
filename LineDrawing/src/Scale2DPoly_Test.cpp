#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "Scale2DPoly.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(1366, 768, 2, "Scale 2D Polygon");

    Scale2DPoly r2DArgs;
    Scale2DPolyArgs args{
        { {200, 50}, {250, 100}, {200, 150},
        {100, 150}, {50, 100}, {100, 50} },
        2
    };

    window.SetAlgorithm(r2DArgs, args);
    window.LoopAndDraw(GREEN);

    return 0;
}