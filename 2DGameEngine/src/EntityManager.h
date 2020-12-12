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
	bool HasEntites() const;
	Entity& AddEntity(std::string entity);
	std::vector<Entity*> getEntities() const;
	unsigned int getEntityCount();

	void ListAllEntities() const;
};

