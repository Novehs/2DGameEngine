#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Constants.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Components/TransformComponent.h"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game() : window(nullptr), isRunning(false), ticksLastFrame(0)
{
	
}

Game::~Game()
{
	
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::LoadLevel(int levelNumber)
{
	Entity& projectile(manager.AddEntity("projectile"));

	projectile.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);

	Entity& projectile2(manager.AddEntity("projectile2"));
	projectile2.AddComponent<TransformComponent>(400, 0, 0, 100, 50, 50, 1);
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

	LoadLevel(0);

	

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
	//wait until time has elapsed since the last frame
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));


	int timeWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	if (timeWait > 0 && timeWait <= FRAME_TARGET_TIME)
		SDL_Delay(timeWait);

	//difference from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.f;

	//clamp delta time to a max value
	//deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//set ticks of current frame for next pass
	ticksLastFrame = SDL_GetTicks();

	manager.Update(deltaTime);
}

void Game::Render()
{
	//set background colour
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

	//clears the back buffer, allowing to draw needed objects
	SDL_RenderClear(renderer);

	//Call manager.render
	if (manager.hasNoEntites())
		return;

	manager.Render();

	//swap front and back buffers
	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	manager.ClearData();
	SDL_Quit();
}
