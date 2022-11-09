#pragma once
#include "DAlg.h"
#include "DDA.h"

#include <iostream>
#include <exception>
#include <algorithm>

extern SDL_Color BLUE;
extern SDL_Color RED;

struct CyrusBeckArgs : public DAlgArgs
{
    using Tp = std::vector<std::pair<int, int>>;
    Tp vertices, line;
    int n;

    CyrusBeckArgs(const Tp& vertices_, const Tp& line_, int n_)
        :vertices(vertices_), line(line_), n(n_)
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

class CyrusBeck : public DAlg
{
public:
    const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs& args) override
    {
        try
        {

            const CyrusBeckArgs& cbArgs = dynamic_cast<const CyrusBeckArgs&>(args);
            using Tp = std::vector<std::pair<int, int>>;
            const Tp& vertices = cbArgs.vertices, line = cbArgs.line;
            int n = cbArgs.n;

            DrawPolygon(vertices, RED);

            Tp ans(2), normal(n);

            for (int i = 0; i < n; i++)
            {
                normal[i].second = vertices[(i + 1) % n].first - vertices[i].first;
                normal[i].first = vertices[i].second - vertices[(i + 1) % n].second;
            }

            std::pair<int, int> P1_P0 = std::make_pair(line[1].first - line[0].first, line[1].second - line[0].second);

            std::vector<std::pair<int, int>> P0_PEi(n);

            for (int i = 0; i < n; i++)
            {
                P0_PEi[i].first = vertices[i].first - line[0].first;
                P0_PEi[i].second = vertices[i].second - line[0].second;
            }

            std::vector<int> numerator(n), denominator(n);
            std::vector<float> tE, tL;

            for (int i = 0; i < n; i++)
            {
                numerator[i] = normal[i].first * P0_PEi[i].first + normal[i].second * P0_PEi[i].second;
                denominator[i] = normal[i].first * P1_P0.first + normal[i].second * P1_P0.second;

                if (denominator[i] > 0)
                    tE.push_back((float)(numerator[i]) / (float)(denominator[i]));
                else
                    tL.push_back((float)(numerator[i]) / (float)(denominator[i]));
            }

            float temp[2];
            temp[0] = *std::max_element(tE.begin(), tE.end());
            temp[1] = *std::max_element(tL.begin(), tL.end());

            if (temp[0] > temp[1])
            {
                ans[0] = std::make_pair(-1, -1);
                ans[1] = std::make_pair(-1, -1);
                
                this->line(ans[0].first, ans[0].second, ans[1].first, ans[1].second);
                return m_Pixels;
            }

            // Calculating the coordinates in terms of x and y
            ans[0].first = (float)line[0].first + (float)P1_P0.first * (float)temp[0];
            ans[0].second = (float)line[0].second + (float)P1_P0.second * (float)temp[0];
            ans[1].first = (float)line[0].first + (float)P1_P0.first * (float)temp[1];
            ans[1].second = (float)line[0].second + (float)P1_P0.second * (float)temp[1];

            this->line(ans[0].first, ans[0].second, ans[1].first, ans[1].second);
            return m_Pixels;
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

    void putpixel(int x, int y, SDL_Color color)
    {
        SDL_Point point{ x, y };
        m_Pixels.emplace_back(point, color);
    }

    void DrawPolygon(const std::vector<std::pair<int, int>>& vertices, SDL_Color color = BLUE)
    {
        int n = vertices.size();
        for (int i = 0; i < n - 1; i++)
            line(vertices[i].first, vertices[i].second, vertices[i + 1].first, vertices[i + 1].second, color);

        line(vertices[0].first, vertices[0].second, vertices[n - 1].first, vertices[n - 1].second, color);
    }
private:
    std::vector<std::pair<SDL_Point, SDL_Color>> m_Pixels;
};