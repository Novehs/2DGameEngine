#include "FontManager.h"
#include "Game.h"
TTF_Font* FontManager::LoadFont(const char* filename, int fontSize)
{
	return TTF_OpenFont(filename, fontSize);
}

void FontManager::Draw(SDL_Texture* texture, SDL_Rect position)
{
	SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
}
