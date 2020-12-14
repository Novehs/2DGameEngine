#pragma once
#include "Game.h"

class Collision
{
public:
	static bool checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};

