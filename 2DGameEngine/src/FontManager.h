#pragma once
#include <SDL_ttf.h>
class FontManager
{
public:
	static TTF_Font* LoadFont(const char* filename, int fontSize);
	static void Draw(SDL_Texture* texture, SDL_Rect position);
};

