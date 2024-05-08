#include "Game.h"

#define WINDOW_TITLE "CUPHEAD ATTACK!"
Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;


	game = new Game();

	game->init(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->SCREEN_WIDTH, game->SCREEN_HEIGHT, 0);
	while (game->running())
	{
		frameStart = SDL_GetTicks(); // Start to count Frame Time
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < frameDelay)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();
	return 0;
}

			