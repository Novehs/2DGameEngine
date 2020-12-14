#include "KeyboardControlComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
KeyboardControlComponent::KeyboardControlComponent() : transform(nullptr), sprite(nullptr), collider(nullptr)
{
}

KeyboardControlComponent::KeyboardControlComponent(std::string up, std::string right, std::string down, std::string left, std::string shoot, std::string collision)
{
	upKey = GetSDLKeyStringCode(up.c_str());
	rightKey = GetSDLKeyStringCode(right.c_str());
	downKey = GetSDLKeyStringCode(down.c_str());
	leftKey = GetSDLKeyStringCode(left.c_str());
	shootKey = GetSDLKeyStringCode(shoot.c_str());
	collisionKey = GetSDLKeyStringCode(collision.c_str());
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
	else if (key.compare("c") == 0)
		return "99";

	return std::to_string(static_cast<int>(key[0]));
}

void KeyboardControlComponent::Initalise()
{
	transform = owner->GetComponent<TransformComponent>();
	sprite = owner->GetComponent<SpriteComponent>();
	collider = owner->GetComponent< ColliderComponent>();
}

void KeyboardControlComponent::Update(float deltaTime)
{
	if(!collider)
		collider = owner->GetComponent< ColliderComponent>();

	if (Game::event.type == SDL_KEYDOWN)
	{
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode.compare(upKey) == 0)
		{
			transform->velocity.y = -100;
			transform->velocity.x = 0;
			sprite->Play("Up");
		}
			
		if (keyCode.compare(downKey) == 0)
		{
			transform->velocity.y = 100;
			transform->velocity.x = 0;
			sprite->Play("Down");
		}
		if (keyCode.compare(rightKey) == 0)
		{
			transform->velocity.y = 0;
			transform->velocity.x = 100;
			sprite->Play("Right");
		}
		if (keyCode.compare(leftKey) == 0)
		{
			transform->velocity.y = 0;
			transform->velocity.x = -100;
			sprite->Play("Left");
		}
		if (keyCode.compare(shootKey) == 0)
		{
			
		}
		if (keyCode.compare(collisionKey) == 0)
		{
			collider->draw = !collider->draw;
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
