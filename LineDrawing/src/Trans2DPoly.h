#pragma once
#include "DAlg.h"
#include "DDA.h"

#include <iostream>
#include <exception>

extern SDL_Color BLUE;
extern SDL_Color WHITE;

struct Trans2DPolyArgs : public DAlgArgs
{
    std::vector<std::pair<int, int>> vertices;
    Trans2DPolyArgs(const std::vector<std::pair<int, int>>& verts)
        :vertices(verts)
    {}
};

static class DDAExt : public DDA
{
public:
    DDAExt(SDL_Color color = BLUE)
        :DDA(color)
    {}

    void ResetPixels()
    {
        m_Pixels.clear();
    }
    void SetColor(SDL_Color color = BLUE)
    {
        m_Color = color;
    }
};

class Trans2DPoly : public DAlg
{
public:
    const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
    {
        try
        {

            const Trans2DPolyArgs& t2Dp = dynamic_cast<const Trans2DPolyArgs&>(args);

            const std::vector<std::pair<int, int>>& vertices = t2Dp.vertices;

            // draw original polygon
            DrawPolygon(vertices, WHITE);
            const auto& shiftedVerts = shift(vertices);
            DrawPolygon(shiftedVerts);
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
    void DrawPolygon(const std::vector<std::pair<int, int>>& vertices, SDL_Color color = BLUE)
    {
        int n = vertices.size();

        for (int i = 0; i < n - 1; i++)
            line(vertices[i].first, vertices[i].second, vertices[i + 1].first, vertices[i + 1].second, color);

        line(vertices[0].first, vertices[0].second, vertices[n - 1].first, vertices[n - 1].second, color);
    }
private:

    void line(int x1, int x2, int y1, int y2, SDL_Color color = BLUE)
    {
        static DDAExt dda;
        dda.SetColor(color);
        const auto& pixels = dda.draw(DDAArgs{ x1, x2, y1, y2 });

        for (const auto& pixel : pixels)
            m_Pixels.emplace_back(pixel.first, pixel.second);

        dda.ResetPixels();
    }

    void putpixel(int x, int y, SDL_Color color)
    {
        SDL_Point point{ x, y };
        m_Pixels.emplace_back(point, color);
    }

    std::vector<std::pair<int, int>> shift(std::vector<std::pair<int, int>> vertices)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            vertices[i].first += 50;
            vertices[i].second += 50;
        }

        return std::move(vertices);
    }

private:
    std::vector<std::pair<SDL_Point, SDL_Color>> m_Pixels;
};