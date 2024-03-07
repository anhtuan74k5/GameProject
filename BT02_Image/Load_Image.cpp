//Load Image
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;


const int WIDTH = 800;
const int HEIGHT = 600;
bool init();
bool loadMedia();
void close();

SDL_Surface* LoadSurface(string path);
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBackGround = NULL;
SDL_Surface* gCharacter = NULL;

//Initialize
bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! Error: " << SDL_GetError();
		success = false;
	}
	else
	{
		//Get window
		gWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
		if (gWindow == NULL)
		{
			cout << "Window can not be created! Error: " << SDL_GetError();
			success = false;
		}
		else {
	
				//Get Window Surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;

	gBackGround = IMG_Load("bikiniBottom.jpg");
	gCharacter = IMG_Load("Spongebob.png");
	if (gBackGround == NULL || gCharacter == NULL)
	{
		cout << "Failed to load PNG image" << endl;
		success = false;
	}
	return success;
}

void close() {
	SDL_FreeSurface(gBackGround);
	gBackGround = NULL;
	SDL_FreeSurface(gCharacter);
	gCharacter = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

}

int main(int argc, char* argv[]) {
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		if (!loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			SDL_BlitSurface(gBackGround, NULL, gScreenSurface, NULL);
			SDL_BlitSurface(gCharacter, NULL, gScreenSurface, NULL);
		}
	}
	SDL_UpdateWindowSurface(gWindow);
	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}
	close();
	return 0;
}
