#pragma once
#include "DAlg.h"

#include <iostream>
#include <exception>

extern SDL_Color BLUE;

struct BresenhamCircleArgs : public DAlgArgs
{
    int x0, y0, rad;
    BresenhamCircleArgs(int x0_, int y0_, int rad_)
        :x0(x0_), y0(y0_), rad(rad_)
    {}
};

class BresenhamCircle : public DAlg
{
public:
    const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
    {
		try
		{

			const BresenhamCircleArgs& bcArgs = dynamic_cast<const BresenhamCircleArgs&>(args);
        
			int x_centre = bcArgs.x0, y_centre = bcArgs.y0;
			int r = bcArgs.rad;
			int x = 0, y = r;

			if (r > 0)
			{
				putpixel(x + x_centre, (y + y_centre), BLUE);
				putpixel(x + x_centre, (-y + y_centre), BLUE);
				putpixel(y + x_centre, (x + y_centre), BLUE);
				putpixel(-y + x_centre, (x + y_centre), BLUE);
			}
			else
			{
				putpixel(x + x_centre, (y + y_centre), BLUE);
			}

			int d = 3 - (2 * r);
			while (x < y)
			{
				x++;

				if (d <= 0)
					d = d + (4 * x) + 6;
				else
				{
					y--;
					d = d + 4 * (x - y) + 10;
				}

				if (y < x)
					break;


				putpixel(x + x_centre, (y + y_centre), BLUE);
				putpixel(-x + x_centre,(y + y_centre), BLUE);
				putpixel(x + x_centre, (-y + y_centre), BLUE);
				putpixel(-x + x_centre, (-y + y_centre), BLUE);

					if (x != y)
					{

						putpixel(y + x_centre, (x + y_centre), BLUE);
						putpixel(-y + x_centre, (x + y_centre), BLUE);
						putpixel(y + x_centre, (-x + y_centre), BLUE);
						putpixel(-y + x_centre, (-x + y_centre), BLUE);
					}
			}
		}
		catch (const std::bad_cast& e)
		{
			std::cout << "Invalid args passed" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
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