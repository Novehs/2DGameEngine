#include "TileComponent.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "../AssetManager.h"

TileComponent::TileComponent(int sourceX, int sourceY, int x, int y, int tileSize, int tileScale, std::string assetTextureID)
{
	texture = Game::assetManager->GetTexture(assetTextureID);
	source.x = sourceX;
	source.y = sourceY;
	source.w = tileSize;
	source.h = tileSize;

	dest.x = x;
	dest.y = y;
	dest.w = tileSize * tileScale;
	dest.h = tileSize * tileScale;

	position.x = x;
	position.y = y;
}

TileComponent::~TileComponent()
{
	SDL_DestroyTexture(texture);
}

void TileComponent::Initalise()
{
}

void TileComponent::Update(float deltaTime)
{
	dest.x = position.x - Game::camera.x;
	dest.y = position.y - Game::camera.y;
}

void TileComponent::Render()
{
	TextureManager::Draw(texture, source, dest, SDL_FLIP_NONE);
}
