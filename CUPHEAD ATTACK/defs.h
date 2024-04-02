#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define WINDOW_TITLE "CUPHEAD ATTACK!"
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_X][MAX_MAP_Y];
	char* file_name;

};
#endif