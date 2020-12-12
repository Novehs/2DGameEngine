#pragma once
#include <map>
#include <string>

class EntityManager;
struct SDL_Texture;

class AssetManager
{
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string textureID, const char* filepath);
	SDL_Texture* GetTexture(std::string textureID);
};

