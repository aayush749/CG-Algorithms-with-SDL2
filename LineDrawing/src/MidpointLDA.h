#pragma once
#include "DAlg.h"

extern SDL_Color BLUE;

struct MidpointLDAArgs : public DAlgArgs
{
    int x0, y0, x1, y1;
    MidpointLDAArgs(int x0_, int y0_, int x1_, int y1_)
        :x0(x0_), y0(y0_), x1(x1_), y1(y1_)
    {}
};

class MidpointLDA : public DAlg
{
public:
    const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
    {
        const MidpointLDAArgs& ddaArgs = static_cast<const MidpointLDAArgs&>(args);
        int x0 = ddaArgs.x0, x1 = ddaArgs.x1;
        int y0 = ddaArgs.y0, y1 = ddaArgs.y1;

        int dx = x1 - x0;
        int dy = y1 - y0;

        float m = (y1 - y0) / (x1 - x0);
        float b = y0 - (m * x0);
        
        if (dy <= dx)
        {
            int d = dy - (dx / 2);
            int x = x0, y = y0;
            
            putpixel(x, y, BLUE);

            while (x < x1)
            {
                x++;
                if (d < 0)
                    d = d + dy;
                else
                {
                    d += (dy - dx);
                    y++;
                }

                putpixel(x, y, BLUE);
            }
        }

        else if (dx < dy)
        {
            int d = dx - (dy / 2);
            int x = x0, y = y0;
            putpixel(x, y, BLUE);

            while (y < y1)
            {
                y++;
                if (d < 0)
                    d = d + dx;
                else
                {
                    d += (dx - dy);
                    x++;
                }


                putpixel(x, y, BLUE);
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