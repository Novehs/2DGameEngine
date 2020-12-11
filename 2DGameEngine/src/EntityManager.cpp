#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"

void EntityManager::ClearData()
{
    for (auto& entity : entities)
        entity->Destroy();
}

void EntityManager::Update(float deltaTime)
{
    for (auto& entity : entities)
        entity->Update(deltaTime);
}

void EntityManager::Render()
{
    for (auto& entity : entities)
        entity->Render();
}

bool EntityManager::hasNoEntites() const
{
    return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName)
{
    Entity* entity = new Entity(*this, entityName);
    entities.emplace_back(entity);

    return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const
{
    return entities;
}

unsigned int EntityManager::getEntityCount()
{
    return entities.size();
}
