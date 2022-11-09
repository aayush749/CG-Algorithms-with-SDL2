#pragma once
#include "DAlg.h"
#include "DDA.h"

#include <iostream>
#include <exception>

extern SDL_Color BLUE;
extern SDL_Color WHITE;

struct Composite2DPolyArgs : public DAlgArgs
{
    using PII = std::pair<int, int>;

    std::vector<std::pair<int, int>> vertices;
    PII translate, pivot;
    int angle;
    Composite2DPolyArgs(const std::vector<std::pair<int, int>>& verts, const PII& translate_, const PII& pivot_, const int angle_)
        :vertices(verts), translate(translate_), pivot(pivot_), angle(angle_)
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

class Composite2DPoly : public DAlg
{
public:
    const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
    {
        try
        {
            const Composite2DPolyArgs& c2Dp = dynamic_cast<const Composite2DPolyArgs&>(args);

            const auto&[vertices, translation, pivot, angle] = c2Dp;

            // draw original polygon
            DrawPolygon(vertices, WHITE);
            const auto& shiftedVerts = shift(vertices, translation);
            DrawPolygon(shiftedVerts, BLUE);
            const auto& compVerts = rotate(shiftedVerts, pivot, angle);
            DrawPolygon(compVerts, { 0xFF, 0x00, 0xFF, 0xFF });
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

    std::vector<std::pair<int, int>> 
    shift(std::vector<std::pair<int, int>> vertices, const std::pair<int, int>& translation = {50, 50})
    {
        const auto[xShift, yShift] = translation;
        for (int i = 0; i < vertices.size(); i++)
        {
            vertices[i].first += xShift;
            vertices[i].second += yShift;
        }

        return std::move(vertices);
    }

    std::vector<std::pair<int, int>>
    rotate(const std::vector<std::pair<int, int>> vertices, const std::pair<int, int> pivotPoints, const int angle)
    {
        int x, y;
        std::vector<std::pair<int, int>> ans(vertices.size());

        const auto [x_pivot, y_pivot] = pivotPoints;

        for (int i = 0; i < vertices.size(); i++)
        {
            x = vertices[i].first - x_pivot;
            y = vertices[i].second - y_pivot;
            ans[i].first = x_pivot + (x * COS(angle) - y * SIN(angle));
            ans[i].second = y_pivot + (x * SIN(angle) + y * COS(angle));
        }

        return std::move(ans);
    }

private:
    double SIN(const int angle) { return sin(angle * 3.141592653589 / 180); }
    double COS(const int angle) { return cos(angle * 3.141592653589 / 180); }

private:
    std::vector<std::pair<SDL_Point, SDL_Color>> m_Pixels;
};