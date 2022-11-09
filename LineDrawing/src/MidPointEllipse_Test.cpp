#include <iostream>
#include <SDL.h>

#include "GfxSubsystem.h"
#include "MidPointEllipse.h"

SDL_Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
SDL_Color RED{ 0xFF, 0x00, 0x00, 0xFF };
SDL_Color GREEN{ 0x00, 0xFF, 0x00, 0xFF };
SDL_Color BLUE{ 0x00, 0x00, 0xFF, 0xFF };

int main(int argc, char** argv)
{

    GfxSubsystem window(640, 480, 2, "Midpoint Ellipse");

    MidPointEllipse mpe;
    MidPointEllipseArgs args{ 0, 0, 100, 50 };

    window.SetAlgorithm(mpe, args);
    window.LoopAndDraw(GREEN);

    return 0;
}