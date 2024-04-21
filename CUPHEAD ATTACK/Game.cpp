#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Header.h"


Game::Game()
{}
Game::~Game()
{}



void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!... " << std::endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		 renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			//SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/plx-1.png");
			
			//SDL_RenderPresent(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else isRunning = false;


	map = new Map();
	player.addComponent<TransformComponent>(450, 350); //starting position
	Enemy_Plane1.addComponent<TransformComponent>(0,80);
	Enemy_Plane2.addComponent<TransformComponent>(900,150);
	Enemy_Plane1.addComponent<SpriteComponent>("assets/Enemy_PlaneRight.png", 4, 100, 99, 112, 75);
	Enemy_Plane2.addComponent<SpriteComponent>("assets/Enemy_PlaneLeft.png", 4, 100, 99, 112, 75);
	Enemy_Pawn1.addComponent<TransformComponent>(0, 350);
	Enemy_Pawn2.addComponent<TransformComponent>(900, 350);
	Enemy_Pawn1.addComponent<SpriteComponent>("assets/Enemy_PawnRight.png", 4, 100, 102, 127, 75);
	Enemy_Pawn2.addComponent<SpriteComponent>("assets/Enemy_PawnLeft.png", 4, 100, 102, 127, 75);

	// move Enemy_plane1 to the right
	Enemy_Plane1.getComponent<TransformComponent>().velocity.x = 1;
	// move Enemy_plane2 to the left
	Enemy_Plane2.getComponent<TransformComponent>().velocity.x = -1;
	// move Enemy_pawn1 to the right
	Enemy_Pawn1.getComponent<TransformComponent>().velocity.x = 1;
	// move Enemy_pawn2 to the left
	Enemy_Pawn2.getComponent<TransformComponent>().velocity.x = -1;

	player.addComponent<SpriteComponent>("assets/Idle_Sprite.png", 4 , 100, 155, 98, 75);
	//player.addComponent<SpriteComponent>("assets/RunLeft_Sprite.png", 4, 100, 155, 135, 75);
	//player.addComponent<SpriteComponent>("assets/RunRight_Sprite.png", 4, 100, 155, 135, 75);
	//player.addComponent<SpriteComponent>("assets/Jump_Sprite.png", 4, 100, 109, 82, 50);

	
	player.addComponent<KeyboardController>();
}






void Game::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {

	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	//player.getComponent<TransformComponent>().position.Add(Vector2D(1, 0));
	
}


void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

