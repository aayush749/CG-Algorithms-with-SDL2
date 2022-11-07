#pragma once
#include <SDL.h>
#include <vector>
#include "DAlg.h"

class GfxSubsystem
{
public:
	GfxSubsystem(const int w, const int h, const int pt_sz, const char* windowName = nullptr);
	SDL_Window* GetWindowPtr() const { return m_Wind; }
	SDL_Renderer* GetRendererPtr() const { return m_Renderer; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void SetAlgorithm(DAlg&, const DAlgArgs&);
	void LoopAndDraw(SDL_Color);

	void DrawAxis(SDL_Color);
	void DrawPoints(const std::vector<SDL_Point>&);
	void DrawPoints(const std::vector<std::pair<SDL_Point, SDL_Color>>&);
	virtual ~GfxSubsystem();
private:
	int width, height, pointSz;
	SDL_Window* m_Wind;
	SDL_Renderer* m_Renderer;
	
	std::vector<std::pair<SDL_Point, SDL_Color>> m_Points;
};