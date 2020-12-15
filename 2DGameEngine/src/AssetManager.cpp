#include "AssetManager.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "FontManager.h"

AssetManager::AssetManager(EntityManager* manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{
    
}

void AssetManager::ClearData()
{
    textures.clear();
    fonts.clear();
}

void AssetManager::AddTexture(std::string textureID, const char* filepath)
{
    textures.emplace(textureID, TextureManager::LoadTexture(filepath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureID)
{
    return textures[textureID];
}

void AssetManager::AddFont(std::string fontID, const char* filepath, int fontSize)
{
    fonts.emplace(fontID, FontManager::LoadFont(filepath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontID)
{
    return fonts[fontID];
}
