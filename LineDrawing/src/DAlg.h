#pragma once

#include <vector>
#include <utility>
#include <SDL.h>

struct DAlgArgs
{
	virtual ~DAlgArgs() {}
};

class DAlg
{
public:
	virtual const std::vector<std::pair<SDL_Point, SDL_Color>>& draw(const DAlgArgs&) = 0;
};