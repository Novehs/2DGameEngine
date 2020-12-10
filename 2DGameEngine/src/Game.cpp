#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Constants.h"

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(120.0f, 90.0f);

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), ticksLastFrame(0)
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
	//wait until time has elapsed since the last frame
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

	int timeWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	if (timeWait > 0 && timeWait <= FRAME_TARGET_TIME)
		SDL_Delay(timeWait);

	//difference from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.f;

	//clamp delta time to a max value
	deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;

	//set ticks of current frame for next pass
	ticksLastFrame = SDL_GetTicks();

	projectilePos = glm::vec2(projectilePos.x + projectileVel.x * deltaTime, projectilePos.y + projectileVel.y * deltaTime);
}

void Game::Render()
{
	//set background colour
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

	//clears the back buffer, allowing to draw needed objects
	SDL_RenderClear(renderer);

	SDL_Rect projectile{ (int)projectilePos.x, (int)projectilePos.y, 10, 10 };

	//Fill object render on renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &projectile);

	//swap front and back buffers
	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
