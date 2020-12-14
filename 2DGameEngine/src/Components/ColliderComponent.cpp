#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height, bool draw)
{
	this->colliderTag = colliderTag;
	this->collider = { x, y, width, height };
	this->draw = draw;
}

void ColliderComponent::Initalise()
{
	collisionTexture = Game::assetManager->GetTexture("collider");

	if (owner->HasComponent<TransformComponent>())
	{
		transform = owner->GetComponent<TransformComponent>();
		source = { 0, 0, transform->width, transform->height };
		dest = { collider.x, collider.y, collider.w, collider.h };
	}
	else
		std::cerr << owner->name << ", does not have a TransformComponent\n";
}

void ColliderComponent::Update(float deltaTime)
{
	collider.x = static_cast<int>(transform->position.x);
	collider.y = static_cast<int>(transform->position.y);
	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;

	dest.x = collider.x - Game::camera.x;
	dest.y = collider.y - Game::camera.y;
}

void ColliderComponent::Render()
{
	if(draw)
		TextureManager::Draw(collisionTexture, source, dest, SDL_FLIP_NONE);
}
