#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include "Game.h"
class GameObject {
public:
	GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y);
	~GameObject();

	void Update();
	void Render();


private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};

#endif