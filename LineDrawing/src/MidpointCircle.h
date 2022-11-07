#pragma once
#include "DAlg.h"

#include <iostream>
#include <exception>

extern SDL_Color BLUE;

struct MidpointCircleArgs : public DAlgArgs
{
	int x0, y0, rad;
	MidpointCircleArgs(int x0_, int y0_, int rad_)
		:x0(x0_), y0(y0_), rad(rad_)
	{}
};

class MidpointCircle : public DAlg
{
public:
	const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
	{
		try
		{

			const MidpointCircleArgs& bcArgs = dynamic_cast<const MidpointCircleArgs&>(args);

			int x_centre = bcArgs.x0, y_centre = bcArgs.y0;
			int r = bcArgs.rad;
			int x = r, y = 0;

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

			int P = 1 - r;
			while (x > y)
			{
				y++;

				if (P <= 0)
					P = P + 2 * y + 1;
				else
				{
					x--;
					P = P + 2 * y - 2 * x + 1;
				}

				if (x < y)
					break;


				putpixel(x + x_centre, (y + y_centre), BLUE);
				putpixel(-x + x_centre, (y + y_centre), BLUE);
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