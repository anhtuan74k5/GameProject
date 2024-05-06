#ifndef _GAME_H_
#define _GAME_H_
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
class Game {
public:
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 600;
	int bulletFlag;
	int numberHeart = 3;
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	void Collision();
	void LoadBackground(const char* filepath);
	void spawnBullet();
	void spawnEnemyBullets();
	void spawnEnemies();
	bool running() { return isRunning; };
	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Texture* backgroundTexture;
	Uint32 lastUpdateTime;


};

#endif