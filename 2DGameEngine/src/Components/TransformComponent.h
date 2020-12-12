#pragma once
#include <glm/glm.hpp>
#include "../Component.h"


class TransformComponent : public Component
{
private:

public:
	glm::vec2 position;
	glm::vec2 velocity;
	int width;
	int height;
	int scale;

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s);

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;

};

