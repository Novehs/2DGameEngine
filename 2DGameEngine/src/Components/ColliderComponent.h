#pragma once
#include "../Component.h"

class TransformComponent;

class ColliderComponent : public Component
{
private:
	
	SDL_Texture* collisionTexture;
	SDL_Rect source;
	SDL_Rect dest;
	TransformComponent* transform;
	
public:
	bool draw;
	SDL_Rect collider;
	std::string colliderTag;
	ColliderComponent(std::string colliderTag, int x, int y, int width, int height, bool draw);

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;
};

