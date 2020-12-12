#include "AssetManager.h"
#include "EntityManager.h"
#include "TextureManager.h"
AssetManager::AssetManager(EntityManager* manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{
    
}

void AssetManager::ClearData()
{
    textures.clear();
}

void AssetManager::AddTexture(std::string textureID, const char* filepath)
{
    textures.emplace(textureID, TextureManager::LoadTexture(filepath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureID)
{
    return textures[textureID];
}
