#pragma once
#include "DAlg.h"

extern SDL_Color BLUE;

struct DDAArgs: public DAlgArgs
{
	int x0, y0, x1, y1;
    DDAArgs(int x0_, int y0_, int x1_, int y1_)
        :x0(x0_), y0(y0_), x1(x1_), y1(y1_)
    {}
};

class DDA : public DAlg
{
public:
    DDA(SDL_Color color = BLUE)
        :m_Color(color)
    {}

	const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
	{
        const DDAArgs& ddaArgs = static_cast<const DDAArgs&>(args);
		int x0 = ddaArgs.x0, x1 = ddaArgs.x1;
		int y0 = ddaArgs.y0, y1 = ddaArgs.y1;

        int dx = x1 - x0;
        int dy = y1 - y0;
        float m = float(dy) / dx, x, y;
        
        if (x0 < x1)
        {
            if (abs(m) >= 0)
            {
                if (m <= 1)
                {
                    x = x0, y = y0;
                    while (x < x1)
                    {
                        x = x + 1;
                        y = y + m;

                        putpixel(round(x), round(y), m_Color);
                    }
                }
                else
                {
                    x = x0, y = y0;
                    while (y < y1)
                    {
                        x = x + 1 / m;
                        y = y + 1;
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
            }
            else
            {
                if (abs(m) <= 1)
                {
                    x = x0, y = y0;
                    while (x < x1)
                    {
                        x = x + 1;
                        y = y - abs(m);
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
                else
                {
                    x = x0, y = y0;
                    while (y > y1)
                    {
                        x = x + 1 / abs(m);
                        y = y - 1;
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
            }
        }
        else
        {
            if (abs(m) >= 0)
            {
                if (m <= 1)
                {
                    x = x0, y = y0;
                    while (x > x1)
                    {
                        x = x - 1;
                        y = y - m;
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
                else
                {
                    x = x0, y = y0;
                    while (y > y1)
                    {
                        x = x - 1 / m;
                        y = y - 1;
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
            }
            else
            {
                if (abs(m) <= 1)
                {
                    x = x0, y = y0;
                    while (x > x1)
                    {
                        x = x - 1;
                        y = y + abs(m);
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
                else
                {
                    x = x0, y = y0;
                    while (y < y1)
                    {
                        x = x - 1 / abs(m);
                        y = y + 1;
                        
                        putpixel(round(x), round(y), m_Color);
                    }
                }
            }
        }
        return m_Pixels;
    }
protected:
    void putpixel(int x, int y, SDL_Color color)
    {
        SDL_Point point{ x, y };
        m_Pixels.emplace_back(point, color);
    }

protected:
    SDL_Color m_Color;
    std::vector<std::pair<SDL_Point, SDL_Color>> m_Pixels;
};