#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game();
	~Game();
	bool IsRunning() const;
	void Initalise(int width, int height);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

