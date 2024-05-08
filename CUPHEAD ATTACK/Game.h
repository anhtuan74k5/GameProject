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
	bool running() { return isRunning; };


	bool checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	void LoadBackground(const char* filepath);
	void spawnBullet();
	void spawnEnemyBullets();
	void spawnEntities();
	void prepareGame();

	static SDL_Renderer* renderer;
	static SDL_Event event;

	void saveHighestScoreToFile(const std::string& filename);
	SDL_Rect playerRect;
	SDL_Rect enemyRect1;
	SDL_Rect enemyRect2;
	SDL_Rect enemyRect3;
	SDL_Rect enemyRect4;
	SDL_Rect bulletRect;
	SDL_Rect EnemyBulletRect1;
	SDL_Rect EnemyBulletRect2;

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Texture* backgroundTexture;
	int score = 0;
	int highestScore = 0;
	bool isGameOver = false;
	bool isGameStarted = false;
	std::string bulletImage = "";

};

#endif