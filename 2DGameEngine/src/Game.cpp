#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Constants.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h";
#include "Components/ColliderComponent.h"
#include "Map.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0, WINDOW_WIDTH, WINDOW_HEIGHT };

Game::Game() : window(nullptr), isRunning(false), ticksLastFrame(0), map(nullptr)
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
	assetManager->AddTexture("tank_right", "./assets/images/tank-tiger-right.png");
	assetManager->AddTexture("chopper", "./assets/images/chopper-spritesheet.png");
	assetManager->AddTexture("radar", "./assets/images/radar-spritesheet.png");
	assetManager->AddTexture("jungle", "./assets/tilemaps/jungle.png");
	assetManager->AddTexture("collider", "./assets/images/collision-texture.png");
	assetManager->AddTexture("helipad", "./assets/images/base-landing.png");

	map = new Map("jungle", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

	Entity& Player(manager.AddEntity("player", LayerType::PLAYER_LAYER));
	Player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	Player.AddComponent<SpriteComponent>("chopper", 2, 90, true, false);
	Player.AddComponent<KeyboardControlComponent>("w", "d", "s", "a","space", "c");
	Player.AddComponent<ColliderComponent>("player", 240, 106, 32, 32, true);

	Entity& Tank(manager.AddEntity("tank", LayerType::ENEMY_LAYER));	//call copy constructor
	Tank.AddComponent<TransformComponent>(150, 500, 5, 0, 32, 32, 1);
	Tank.AddComponent<SpriteComponent>("tank_right");
	Tank.AddComponent<ColliderComponent>("tank", 150, 500, 32, 32, false);

	Entity& Radar(manager.AddEntity("radar", LayerType::UI_LAYER));
	Radar.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	Radar.AddComponent<SpriteComponent>("radar", 8, 150, false, true);

	Entity& Flag = manager.AddEntity("flag", LayerType::LANDMARK_LAYER);
	Flag.AddComponent<TransformComponent>(450, 400, 0, 0, 64, 64, 1);
	Flag.AddComponent<SpriteComponent>("helipad");
	Flag.AddComponent<ColliderComponent>("flag", 450, 400, 64, 64, false);
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
		std::cerr << "Failed to create SDL Renderer" << std::endl;
		return;
	}

	LoadLevel(0);

	isRunning = true;

}

void Game::ProcessInput()
{
	
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

	if(manager.HasEntites())
		manager.Update(deltaTime);

	HandleCameraMovement();

	checkCollisions();
}

void Game::Render()
{
	//set background colour
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

	//clears the back buffer, allowing to draw needed objects
	SDL_RenderClear(renderer);

	//Call manager.render
	if (manager.HasEntites())
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

void Game::HandleCameraMovement()
{
	TransformComponent* playerTransform;

	auto it = manager.getEntitiesByLayer(LayerType::PLAYER_LAYER);

	for (auto& entity : it)
	{
		if (entity->name == "player")
		{
			playerTransform = entity->GetComponent<TransformComponent>();
			camera.x = static_cast<int>(playerTransform->position.x) - (WINDOW_WIDTH / 2);
			camera.y = static_cast<int>(playerTransform->position.y) - (WINDOW_HEIGHT / 2);

		}
		else
		{
			std::cerr << "failed to find player\n";
		}
	}
	
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;

	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;


}

void Game::CheckEntityCollisions()
{
	Entity player = *manager.getEntitiesByLayer(LayerType::PLAYER_LAYER)[0];
	std::string collisionTagType = manager.CheckEntityCollisions(player);

	if (collisionTagType.compare("tank") == 0)
	{
		std::cout << collisionTagType << '\n';
		//isRunning = false;
	}

}

void Game::checkCollisions()
{
	CollisionType collisionType = manager.CheckCollisions();

	if (collisionType == CollisionType::PLAYER_ENEMY_COLLISION)
		std::cout << "enemy collision\n";
	if (collisionType == CollisionType::PLAYER_PROJECTILE_COLLISION)
		std::cout << "player projectile collision\n";
	if (collisionType == CollisionType::ENEMY_PROJECTILE_COLLISION)
		std::cout << "enemy projectile collision\n";
	if (collisionType == CollisionType::PLAYER_LEVEL_COMPLETE_COLLISION)
		std::cout << "level completed collision\n";
}
