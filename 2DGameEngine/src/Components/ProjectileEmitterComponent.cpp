#include "ProjectileEmitterComponent.h"
#include "TransformComponent.h"
ProjectileEmitterComponent::ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop)
{
	this->speed = speed;
	this->angleRad = glm::radians(static_cast<float>(angleDeg));
	this->range = range;
	this->shouldLoop = shouldLoop;
}

void ProjectileEmitterComponent::Initalise()
{
	transform = owner->GetComponent<TransformComponent>();
	origin = glm::vec2(transform->position.x, transform->position.y);
	transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
}

void ProjectileEmitterComponent::Update(float deltaTime)
{
	if (glm::distance(transform->position, origin) > range)
	{
		if (shouldLoop)
		{
			transform->position.x = origin.x;
			transform->position.y = origin.y;
		}
		else
		{
			owner->Destroy();
		}
	}
}

void ProjectileEmitterComponent::Render()
{
}
