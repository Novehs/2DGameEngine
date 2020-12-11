#pragma once
#include <vector>
#include <string>

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
	bool hasNoEntites() const;
	Entity& AddEntity(std::string entity);
	std::vector<Entity*> getEntities() const;
	unsigned int getEntityCount();
};

