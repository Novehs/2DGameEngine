#include "TextureManager.h"
#include "Game.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);

	if (!surface)
	{
		std::cout << filename << '\n';
		std::cout << "failed to load file.\n\n";
	}
		

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dst, 0, nullptr, flip);
}
