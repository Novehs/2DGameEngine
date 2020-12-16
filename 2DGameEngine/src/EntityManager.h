#pragma once
#include <vector>
#include <string>
#include "Constants.h"

class Entity;

class Component;

class EntityManager
{
private:
	std::vector<Entity*> entities;
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasEntites() const;
	Entity& AddEntity(std::string entity, LayerType layer);
	std::vector<Entity*> getEntities() const;
	std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
	unsigned int getEntityCount();
	void DestroyInActiveEntities();
	void ListAllEntities() const;
	std::string CheckEntityCollisions(Entity& entity) const;

	CollisionType CheckCollisions() const;
};

