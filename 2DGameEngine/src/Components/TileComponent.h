#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect dest;
	glm::vec2 position;

	TileComponent(int sourceX, int sourceY, int x, int y, int tileSize, int tileScale, std::string assetTextureID);
	~TileComponent();

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;
};

