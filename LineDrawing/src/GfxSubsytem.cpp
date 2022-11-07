#include "GfxSubsystem.h"
#include <iostream>

GfxSubsystem::GfxSubsystem(const int w, const int h, 
    const int pt_sz, const char* windowName)
	:width(w), height(h), pointSz(pt_sz), m_Wind(nullptr), m_Renderer(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cout << "Initialization failed" 
                  << std::endl;
        exit(1);
    }

    if (!windowName)
        windowName = "Test";

    SDL_Window* window = SDL_CreateWindow(windowName,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        width, height, SDL_WINDOW_SHOWN);

    m_Wind = window;
    if (!m_Wind) 
    {
        SDL_Quit();
        exit(2);
    }

    // initialize renderer
    SDL_Renderer* rendererPtr = SDL_CreateRenderer(
                                           m_Wind, 0, 
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                        );
    m_Renderer = rendererPtr;
}

static SDL_Rect GetRectFromPoint(SDL_Point p, const int pointSz)
{
    SDL_Rect rect;
    rect.x = p.x - pointSz / 2;
    rect.y = p.y - pointSz / 2;

    rect.w = pointSz;
    rect.h = pointSz;


    return std::move(rect);
}

void GfxSubsystem::DrawAxis(SDL_Color color)
{
    // Clear before drawing
    SDL_RenderClear(m_Renderer);

    SDL_Color prevColor;
    SDL_GetRenderDrawColor(m_Renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    
    SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_Renderer, width/2, height, width/2, 0);
    SDL_RenderDrawLine(m_Renderer, width, height/2, 0, height/2);

    SDL_RenderPresent(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, prevColor.a, prevColor.g, prevColor.b, prevColor.a);
}

void GfxSubsystem::DrawPoints(const std::vector<SDL_Point>& points)
{
    // Clear before drawing
    //SDL_RenderClear(m_Renderer);

    SDL_Color prevColor;
    SDL_GetRenderDrawColor(m_Renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);


    for (const auto point : points)
    {
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Point modPoint{ point };
        modPoint.x += width / 2;
        modPoint.y *= -1;
        modPoint.y += height / 2;
        SDL_Rect pointRect = GetRectFromPoint(modPoint, pointSz);
        SDL_RenderDrawRect(m_Renderer, &pointRect);
    }

    SDL_RenderPresent(m_Renderer);
    // Set the color to what was before
    SDL_SetRenderDrawColor(m_Renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void GfxSubsystem::DrawPoints(const std::vector<std::pair<SDL_Point, SDL_Color>>& points)
{
    // Clear before drawing
    //SDL_RenderClear(m_Renderer);
    SDL_Color prevColor;
    SDL_GetRenderDrawColor(m_Renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);

    for (const auto& point : points)
    {
        SDL_Color color = point.second;
        SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
        SDL_Point modPoint{ point.first };
        modPoint.x += width / 2;
        modPoint.y *= -1;
        modPoint.y += height / 2;
        SDL_Rect pointRect = GetRectFromPoint(modPoint, pointSz);
        SDL_RenderDrawRect(m_Renderer, &pointRect);
    }

    SDL_RenderPresent(m_Renderer);
    // Set the color to what was before
    SDL_SetRenderDrawColor(m_Renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

GfxSubsystem::~GfxSubsystem()
{
    SDL_DestroyWindow(m_Wind);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
}

void GfxSubsystem::SetAlgorithm(DAlg& alg, const DAlgArgs& args)
{
    m_Points.clear();

    m_Points = alg.draw(args);
}

void GfxSubsystem::LoopAndDraw(SDL_Color axisColor)
{
    bool quit = false;
    SDL_Event event;

    DrawAxis(axisColor);
    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        DrawPoints(m_Points);
    }
}