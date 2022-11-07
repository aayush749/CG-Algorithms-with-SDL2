#pragma once
#include "DAlg.h"

extern SDL_Color BLUE;

struct BresenhamArgs : public DAlgArgs
{
    int x0, y0, x1, y1;
    BresenhamArgs(int x0_, int y0_, int x1_, int y1_)
        :x0(x0_), y0(y0_), x1(x1_), y1(y1_)
    {}
};

class BresenhamAlg : public DAlg
{
public:
    void ResetPixels()
    {
        m_Pixels.clear();
    }

    const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
    {
        const BresenhamArgs& ddaArgs = static_cast<const BresenhamArgs&>(args);
        int x0 = ddaArgs.x0, x1 = ddaArgs.x1;
        int y0 = ddaArgs.y0, y1 = ddaArgs.y1;

        int dx = x1 - x0;
        int dy = y1 - y0;
        int x = x0;
        int y = y0;
        int p = 2 * dy - dx;

        float m = (y1 - y0) / (x1 - x0);
        float b = y0 - (m * x0);
        

        if (m <= 1)
        {
            while (x < x1)
            {
                if (p >= 0)
                {
                    putpixel(x, y, BLUE);
                    y = y + 1;
                    p = p + 2 * dy - 2 * dx;
                }
                else
                {
                    putpixel(x, y, BLUE);
                    p = p + 2 * dy;
                }
                x = x + 1;
            }
        }
        else
        {
            while (y < y1)
            {
                if (p >= 0)
                {
                    putpixel(x, y, BLUE);
                    x = x + 1;
                    p = p + 2 * dx - 2 * dy;
                }
                else
                {
                    putpixel(x, y, BLUE);
                    p = p + 2 * dx;
                }
                y = y + 1;
            }
        }
        return m_Pixels;
    }
private:
    void putpixel(int x, int y, SDL_Color color)
    {
        SDL_Point point{ x, y };
        m_Pixels.emplace_back(point, color);
    }

private:
    std::vector<std::pair<SDL_Point, SDL_Color>> m_Pixels;
};