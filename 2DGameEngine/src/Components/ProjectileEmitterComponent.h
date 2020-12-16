#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

class TransformComponent;

class ProjectileEmitterComponent : public Component
{
private:
	TransformComponent* transform;
	glm::vec2 origin;
	int speed;
	int range;
	float angleRad;
	bool shouldLoop;

public:
	ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop);

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;


};