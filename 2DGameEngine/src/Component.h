#pragma once
#include "Entity.h"

class Component
{
private:

public:
	Entity* owner;
	virtual ~Component() {}
	virtual void Initalise() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

