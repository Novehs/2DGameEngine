#include "SpriteComponent.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "TransformComponent.h"

SpriteComponent::SpriteComponent(const char* textureID) : spriteFlip(SDL_FLIP_NONE)
{
	isAnimated = false;
	isFixed = false;
	animationIndex = 0;
	SetTexture(textureID);
}

SpriteComponent::SpriteComponent(std::string textureID, int numFrames, int animationSpeed, bool hasDirection, bool isFixed)
{
	isAnimated = true;
	this->numFrames = numFrames;
	this->animationSpeed = animationSpeed;
	this->isFixed = isFixed;

	if (hasDirection)
	{
		Animation Down = Animation(2, numFrames, animationSpeed);
		Animation Right = Animation(1, numFrames, animationSpeed);
		Animation Left = Animation(3, numFrames, animationSpeed);
		Animation Up = Animation(0, numFrames, animationSpeed);

		animations.emplace("Down", Down);
		animations.emplace("Right", Right);
		animations.emplace("Left", Left);
		animations.emplace("Up", Up);

		this->animationIndex = 0;
		this->currentAnimationName = "Down";
	}
	else
	{
		Animation singleAnimation = Animation(0, numFrames, animationSpeed);
		animations.emplace("SingleAnimation", singleAnimation);
		this->animationIndex = 0;
		this->currentAnimationName = "SingleAnimation";
	}

	Play(currentAnimationName);
	SetTexture(textureID);
}

void SpriteComponent::Play(std::string animationName)
{
	this->numFrames = animations[animationName].numFrames;
	this->animationIndex = animations[animationName].index;
	this->animationSpeed = animations[animationName].animationSpeed;
	currentAnimationName = animationName;
}

void SpriteComponent::SetTexture(std::string assetTextureID)
{
	texture = Game::assetManager->GetTexture(assetTextureID);
}

void SpriteComponent::Initalise()
{
	transform = owner->GetComponent<TransformComponent>();
	source.x = 0;
	source.y = 0;
	source.w = transform->width;
	source.h = transform->height;
}

void SpriteComponent::Update(float deltaTime)
{
	if (isAnimated)
	{
		//moves source from first image to last and back to begining
		source.x = source.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
	}

	//move sprite sheet source down by height amount
	source.y = animationIndex * transform->height;

	dest.x = static_cast<int>(transform->position.x) - (isFixed? 0 : Game::camera.x);
	dest.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
	dest.w = transform->width * transform->scale;
	dest.h = transform->height * transform->scale;
}

void SpriteComponent::Render()
{
	TextureManager::Draw(texture, source, dest, spriteFlip);
}
