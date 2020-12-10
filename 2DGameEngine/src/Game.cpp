#include "Game.h"
#include <iostream>
#include "Constants.h"

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = .05f;
float projectileVelY = .05f;

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false)
{
}

Game::~Game()
{
	
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::Initalise(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error Initalising SDL." << std::endl;
		return;
	}

	window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		std::cerr << "Failed to create SDL Window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cerr << "Failed to create SDL Renderer." << std::endl;
		return;
	}

	isRunning = true;
}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	projectilePosX += projectileVelX;
	projectilePosY += projectileVelY;
}

void Game::Render()
{
	//clear render screen and draw colour
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_Rect projectile{ (int)projectilePosX, (int)projectilePosY, 10, 10 };

	//Fill object render on renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &projectile);

	//update renderer (double buffer)
	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
