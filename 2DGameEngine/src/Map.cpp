#include "Map.h"
#include "Game.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"
#include <fstream>

extern EntityManager manager;
Map::Map(std::string textureID, int scale, int tileSize)
{
	this->textureID = textureID;
	this->scale = scale;
	this->tileSize = tileSize;
}

Map::~Map()
{

}

void Map::LoadMap(std::string filepath, int mapSizeX, int mapSizeY)
{
	std::fstream mapFile;
	mapFile.open(filepath);

	if (!mapFile.is_open())
	{
		std::cerr << "file failed to open\n";
		return;
	}

	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			char ch;
			mapFile.get(ch);
			int sourceY = atoi(&ch)* tileSize;
			mapFile.get(ch);
			int sourceX = atoi(&ch)* tileSize;

			AddTile(sourceX, sourceY, x * (scale * tileSize), y * (scale * tileSize));
			mapFile.ignore();
		}
	}

	mapFile.close();

}

void Map::AddTile(int sourceX, int sourceY, int x, int y)
{
	Entity& Tile(manager.AddEntity("tile"));
	Tile.AddComponent<TileComponent>(sourceX, sourceY, x, y, tileSize, scale, textureID);
}
