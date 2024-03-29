#include "graphics.h"
#include "defs.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture("img/plx-1.png");
    graphics.prepareScene(background);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_Texture* MainChar = graphics.loadTexture("img/Main Objects/MainCharacter_RIGHT.png");
    graphics.renderTexture(MainChar, 240, 155);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_DestroyTexture(MainChar);
    MainChar = NULL;
    SDL_DestroyTexture(background);
    background = NULL;

    graphics.quit();
    return 0;
}