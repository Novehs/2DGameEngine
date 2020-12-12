#pragma once
#include "../Component.h"
#include "../Game.h"
#include "../Animation.h"

class TransformComponent;


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect dest;
	SDL_RendererFlip spriteFlip;
	bool isAnimated;
	int numFrames;
	int animationSpeed;
	bool isFixed;	//if fixed, it stays in the same position regardless (e.g. labels)
	std::map<std::string, Animation> animations;
	std::string currentAnimationName;
	unsigned int animationIndex;

public:

	SpriteComponent(const char* textureID);
	SpriteComponent(std::string textureID, int numFrames, int animationSpeed, bool hasDirection, bool isFixed);

	void Play(std::string animationName);
	void SetTexture(std::string assetTextureID);

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;
};

