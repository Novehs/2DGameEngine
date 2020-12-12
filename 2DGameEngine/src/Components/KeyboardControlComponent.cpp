#include "KeyboardControlComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
KeyboardControlComponent::KeyboardControlComponent() : transform(nullptr), sprite(nullptr)
{
}

KeyboardControlComponent::KeyboardControlComponent(std::string up, std::string right, std::string down, std::string left, std::string shoot)
{
	upKey = GetSDLKeyStringCode(up.c_str());
	rightKey = GetSDLKeyStringCode(right.c_str());
	downKey = GetSDLKeyStringCode(down.c_str());
	leftKey = GetSDLKeyStringCode(left.c_str());
	shootKey = GetSDLKeyStringCode(shoot.c_str());
}

std::string KeyboardControlComponent::GetSDLKeyStringCode(std::string key)
{
	if (key.compare("up") == 0)
		return "1073741906";
	else if (key.compare("down") == 0)
		return "1073741905";
	else if (key.compare("right") == 0)
		return "1073741903";
	else if (key.compare("left") == 0)
		return "1073741904";
	else if (key.compare("space") == 0)
		return "32";

	return std::to_string(static_cast<int>(key[0]));
}

void KeyboardControlComponent::Initalise()
{
	transform = owner->GetComponent<TransformComponent>();
	sprite = owner->GetComponent<SpriteComponent>();
}

void KeyboardControlComponent::Update(float deltaTime)
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode.compare(upKey) == 0)
		{
			transform->velocity.y = -50;
			transform->velocity.x = 0;
			sprite->Play("Up");
		}
			
		if (keyCode.compare(downKey) == 0)
		{
			transform->velocity.y = 50;
			transform->velocity.x = 0;
			sprite->Play("Down");
		}
		if (keyCode.compare(rightKey) == 0)
		{
			transform->velocity.y = 0;
			transform->velocity.x = 50;
			sprite->Play("Right");
		}
		if (keyCode.compare(leftKey) == 0)
		{
			transform->velocity.y = 0;
			transform->velocity.x = -50;
			sprite->Play("Left");
		}
		if (keyCode.compare(shootKey) == 0)
		{
			//TODO:...
		}
	}

	if (Game::event.type == SDL_KEYUP)
	{
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);
		if (keyCode.compare(upKey) == 0)
			transform->velocity.y = 0;
		if (keyCode.compare(downKey) == 0)
			transform->velocity.y = 0;
		if (keyCode.compare(rightKey) == 0)
			transform->velocity.x = 0;
		if (keyCode.compare(leftKey) == 0)
			transform->velocity.x = 0;
	}
}

void KeyboardControlComponent::Render()
{
}
