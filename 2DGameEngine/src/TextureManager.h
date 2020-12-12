#pragma once
#include <SDL_render.h>
struct SDL_Texture;
struct SDL_Rect;


class TextureManager
{
private:

public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip);
};
