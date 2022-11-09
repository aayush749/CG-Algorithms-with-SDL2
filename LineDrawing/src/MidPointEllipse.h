#pragma once
#include "DAlg.h"

#include <iostream>
#include <exception>

extern SDL_Color BLUE;
extern SDL_Color WHITE;

struct MidPointEllipseArgs : public DAlgArgs
{
	int x0, y0, rad_x, rad_y;
	MidPointEllipseArgs(int x0_, int y0_, int rad_x_, int rad_y_)
		:x0(x0_), y0(y0_), rad_x(rad_x_), rad_y(rad_y_)
	{}
};

class MidPointEllipse : public DAlg
{
public:
	const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
	{
		try
		{

			const MidPointEllipseArgs& mpeArgs = dynamic_cast<const MidPointEllipseArgs&>(args);

			int xc = mpeArgs.x0, yc = mpeArgs.y0;
			int rx = mpeArgs.rad_x, ry = mpeArgs.rad_y;
			
            float dx, dy, d1, d2, x, y;
            x = 0;
            y = ry;

            d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
            dx = 2 * ry * ry * x;
            dy = 2 * rx * rx * y;

            while (dx < dy)
            {
                putpixel(x + xc, (y + yc), WHITE);
                putpixel(-x + xc,(y + yc), WHITE);
                putpixel(x + xc, (-y + yc), WHITE);
                putpixel(-x + xc, (-y + yc), WHITE);
                if (d1 < 0)
                {
                    x++;
                    dx = dx + (2 * ry * ry);
                    d1 = d1 + dx + (ry * ry);
                }
                else
                {
                    x++;
                    y--;
                    dx = dx + (2 * ry * ry);
                    dy = dy - (2 * rx * rx);
                    d1 = d1 + dx - dy + (ry * ry);
                }
            }

            d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

            while (y >= 0)
            {
                
                
                
                
                putpixel(x + xc, (y + yc), WHITE);
                putpixel(-x + xc, (y + yc), WHITE);
                putpixel(x + xc, (-y + yc), WHITE);
                putpixel(-x + xc, (-y + yc), WHITE);

                if (d2 > 0)
                {
                    y--;
                    dy = dy - (2 * rx * rx);
                    d2 = d2 + (rx * rx) - dy;
                }
                else
                {
                    y--;
                    x++;
                    dx = dx + (2 * ry * ry);
                    dy = dy - (2 * rx * rx);
                    d2 = d2 + dx - dy + (rx * rx);
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