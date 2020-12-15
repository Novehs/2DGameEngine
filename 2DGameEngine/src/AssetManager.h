#pragma once
#include <map>
#include <string>
#include <SDL_ttf.h>

class EntityManager;
struct SDL_Texture;

class AssetManager
{
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string textureID, const char* filepath);
	SDL_Texture* GetTexture(std::string textureID);

	void AddFont(std::string fontID, const char* filepath, int fontSize);
	TTF_Font* GetFont(std::string fontID);
};

