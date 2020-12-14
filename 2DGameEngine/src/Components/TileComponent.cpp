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

	position.x = (float)x;
	position.y = (float)y;
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
	dest.x = static_cast<int>(position.x) - Game::camera.x;
	dest.y = static_cast<int>(position.y) - Game::camera.y;
}

void TileComponent::Render()
{
	TextureManager::Draw(texture, source, dest, SDL_FLIP_NONE);
}
