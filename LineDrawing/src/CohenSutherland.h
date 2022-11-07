#pragma once
#include "DAlg.h"
#include "DDA.h"

#include <iostream>
#include <exception>

extern SDL_Color BLUE;
extern SDL_Color RED;

struct CohenSutherlandArgs : public DAlgArgs
{
	int px, py, qx, qy, x_min, x_max, y_min, y_max;
	CohenSutherlandArgs(int px_, int py_, int qx_, int qy_, int x_min_, int x_max_, int y_min_, int y_max_)
		:px(px_), py(py_), qx(qx_), qy(qy_), x_min(x_min_), x_max(x_max_), y_min(y_min_), y_max(y_max_)
	{}
};

static class DDAExt : public DDA
{
public:
    void ResetPixels()
    {
        m_Pixels.clear();
    }
};

class CohenSutherland : public DAlg
{
public:
	const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
	{
		try
		{

			const CohenSutherlandArgs& csArgs = dynamic_cast<const CohenSutherlandArgs&>(args);
			
			int px = csArgs.px, py = csArgs.py, qx = csArgs.qx, 
				qy = csArgs.qy, x_min = csArgs.x_min, x_max = csArgs.x_max,
				y_min = csArgs.y_min, y_max = csArgs.y_max;
			

            int pcode = getRegionCode(px, py, x_min, x_max, y_min, y_max);
            int qcode = getRegionCode(qx, qy, x_min, x_max, y_min, y_max);


            rectangle_wind(x_min, y_min, x_max, y_max);

            if (pcode == 0 && qcode == 0) {
                line(px, py, qx, qy);
            }
            else if ((pcode & qcode) != 0) {
                line(px, py, qx, qy);
            }
            else
            {
                while (true)
                {
                    if (pcode == 0 && qcode == 0) // line is inside the window
                        break;
                    else if ((pcode & qcode) != 0) // line is outside the window
                        break;
                    else // line is still partially inside
                    {
                        double x, y;
                        int code;
                        if (pcode != 0)
                            code = pcode;
                        else
                            code = qcode;

                        if (code & 8) // line cuts at top of window
                        {
                            x = px + (qx - px) * (y_max - py) / (qy - py);
                            y = y_max;
                        }
                        else if (code & 4) // line cuts at bottom of window
                        {
                            x = px + (qx - px) * (y_min - py) / (qy - py);
                            y = y_min;
                        }
                        else if (code & 2) // line cuts at right of window
                        {
                            y = py + (qy - py) * (x_max - px) / (qx - px);
                            x = x_max;
                        }
                        else if (code & 1) // line cuts at left of window
                        {
                            y = py + (qy - py) * (x_min - px) / (qx - px);
                            x = x_min;
                        }

                        if (code == pcode)
                        {
                            px = round(x);
                            py = round(y);
                            pcode = getRegionCode(px, py, x_min, x_max, y_min, y_max);
                        }
                        else
                        {
                            qx = round(x);
                            qy = round(y);
                            qcode = getRegionCode(qx, qy, x_min, x_max, y_min, y_max);
                        }
                    }
                }
                line(px, py, qx, qy);
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
	void line(int x1, int x2, int y1, int y2, SDL_Color color = BLUE)
	{
        static DDAExt dda;
        const auto& pixels = dda.draw(DDAArgs{ x1, x2, y1, y2 });
        
        for (const auto& pixel : pixels)
            m_Pixels.emplace_back(pixel.first, pixel.second);
        
        dda.ResetPixels();
	}

    void rectangle_wind(int xmin, int ymin, int xmax, int ymax)
    {
        int x, y;
        y = ymin;
        for (x = xmin; x <= xmax; x++)
            putpixel(x, y, RED);
        y = ymax;
        for (x = xmin; x <= xmax; x++)
            putpixel(x, y, RED);
        x = xmin;
        for (y = ymin; y <= ymax; y++)
            putpixel(x, y, RED);
        x = xmax;
        for (y = ymin; y <= ymax; y++)
            putpixel(x, y, RED);
    }

    void putpixel(int x, int y, SDL_Color color)
    {
        SDL_Point point{ x, y };
        m_Pixels.emplace_back(point, color);
    }

    int getRegionCode(int x, int y, int x_min, int x_max, int y_min, int y_max)
    {
        int code = 0;

        if (x < x_min)
            code = code | 1; // 0001 left
        else if (x > x_max)
            code = code | 2; // 0010 right
        if (y < y_min)
            code = code | 4; // 0100 bottom
        else if (y > y_max)
            code = code | 8; // 1000 top

        return code;
    }
private:
	std::vector<std::pair<SDL_Point, SDL_Color>> m_Pixels;
};