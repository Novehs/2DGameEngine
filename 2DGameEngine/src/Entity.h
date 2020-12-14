#pragma once
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <iostream>

class EntityManager;
class Component;
enum class LayerType;
class Entity
{
private:
	EntityManager& manager;
	bool isActive;
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentType;
public:
	std::string name;
	LayerType layer;
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name, LayerType layer);

	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args)
	{
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		componentType[&typeid(*newComponent)] = newComponent;
		newComponent->Initalise();

		return *newComponent;
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(componentType[&typeid(T)]);
	}

	template<typename T>
	bool HasComponent() const
	{
		return componentType.count(&typeid(T));
	}

	void ListAllComponents() const;
};

