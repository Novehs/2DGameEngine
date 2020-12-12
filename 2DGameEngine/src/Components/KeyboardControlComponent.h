#pragma once
#include "../Component.h"

class TransformComponent;
class SpriteComponent;

class KeyboardControlComponent : public Component
{
private:

public:
	std::string upKey;
	std::string downKey;
	std::string rightKey;
	std::string leftKey;
	std::string shootKey;
	TransformComponent* transform;
	SpriteComponent* sprite;

	KeyboardControlComponent();
	KeyboardControlComponent(std::string up, std::string right, std::string down, std::string left, std::string shoot);

	std::string GetSDLKeyStringCode(std::string key);

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;
};

