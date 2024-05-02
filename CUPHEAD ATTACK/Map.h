#ifndef _MAP_H_
#define _MAP_H_

#include "Game.h"

class Map
{
public:
	Map();
	~Map();
	
	void LoadMap(int arr[19][32]);
	void DrawMap();
	int map[19][32];

private:
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

};


#endif