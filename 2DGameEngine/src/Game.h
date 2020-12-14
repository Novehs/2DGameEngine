#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class AssetManager;
class Map;

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	int ticksLastFrame;

public:
	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	static SDL_Rect camera;
	Map* map;
	Game();
	~Game();
	bool IsRunning() const;
	void LoadLevel(int levelNumber);
	void Initalise(int width, int height);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	void HandleCameraMovement();
	void CheckCollisions();
	
};

