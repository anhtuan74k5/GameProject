#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Header.h"
#include <SDL_mixer.h> // Thêm th? vi?n SDL_mixer

#include <cstdlib>
#include <ctime>

SDL_Rect playerRect;
SDL_Rect enemyRect1;
SDL_Rect enemyRect2;
SDL_Rect enemyRect3;
SDL_Rect enemyRect4;
SDL_Rect bulletshoot;

void spawnEnemies()
{
    srand(time(NULL));
    int randomNumber = rand() % 1000;
    if (randomNumber < 10)
    {
        Enemy_Plane1.addComponent<TransformComponent>(0, 80);
        Enemy_Plane2.addComponent<TransformComponent>(900, 150);
        Enemy_Pawn1.addComponent<TransformComponent>(0, 350);
        Enemy_Pawn2.addComponent<TransformComponent>(900, 350);
        Enemy_Plane1.addComponent<SpriteComponent>("assets/Enemy_PlaneRight.png", 4, 100, 99, 112, 75);
        Enemy_Plane2.addComponent<SpriteComponent>("assets/Enemy_PlaneLeft.png", 4, 100, 99, 112, 75);
        Enemy_Pawn1.addComponent<SpriteComponent>("assets/Enemy_PawnRight.png", 4, 100, 102, 127, 75);
        Enemy_Pawn2.addComponent<SpriteComponent>("assets/Enemy_PawnLeft.png", 4, 100, 102, 127, 75);
        // Move Enemy_plane1 to the right
        Enemy_Plane1.getComponent<TransformComponent>().velocity.x = 1;
        // Move Enemy_plane2 to the left
        Enemy_Plane2.getComponent<TransformComponent>().velocity.x = -1;
        // Move Enemy_pawn1 to the right
        Enemy_Pawn1.getComponent<TransformComponent>().velocity.x = 1;
        // Move Enemy_pawn2 to the left
        Enemy_Pawn2.getComponent<TransformComponent>().velocity.x = -1;
    }
}

Game::Game()
{}
Game::~Game()
{}

void Game::LoadBackground(const char* filepath)
{
    SDL_Surface* tmpSurface = IMG_Load(filepath);
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if (!backgroundTexture)
    {
        std::cout << "Failed to load background texture: " << SDL_GetError() << std::endl;
    }
}

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
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }
    else isRunning = false;

    LoadBackground("assets/background.png");
    map = new Map();

    // Kh?i t?o âm thanh n?n
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL Audio initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    // Load và phát nh?c n?n
    Mix_Music* backgroundMusic = Mix_LoadMUS("assets/rainforestambience.wav");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    else {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    // Kh?i t?o các ??i t??ng và các thành ph?n c?a chúng
    player.addComponent<TransformComponent>(685, 150);
    player.addComponent<SpriteComponent>("assets/Idle_Sprite.png", 4, 100, 155, 98, 75);
    player.addComponent<KeyboardController>();

    Enemy_Plane1.addComponent<TransformComponent>(0, 80);
    Enemy_Plane1.addComponent<SpriteComponent>("assets/Enemy_PlaneRight.png", 4, 100, 99, 112, 75);
    Enemy_Plane1.getComponent<TransformComponent>().velocity.x = 1;

    Enemy_Plane2.addComponent<TransformComponent>(900, 150);
    Enemy_Plane2.addComponent<SpriteComponent>("assets/Enemy_PlaneLeft.png", 4, 100, 99, 112, 75);
    Enemy_Plane2.getComponent<TransformComponent>().velocity.x = -1;

    Enemy_Pawn1.addComponent<TransformComponent>(0, 350);
    Enemy_Pawn1.addComponent<SpriteComponent>("assets/Enemy_PawnRight.png", 4, 100, 102, 127, 75);
    Enemy_Pawn1.getComponent<TransformComponent>().velocity.x = 1;

    Enemy_Pawn2.addComponent<TransformComponent>(900, 350);
    Enemy_Pawn2.addComponent<SpriteComponent>("assets/Enemy_PawnLeft.png", 4, 100, 102, 127, 75);
    Enemy_Pawn2.getComponent<TransformComponent>().velocity.x = -1;

    // Kh?i t?o viên ??n
    Bullet.addComponent<TransformComponent>(player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y);
    Bullet.addComponent<SpriteComponent>("assets/bullet.png", 4, 100, 155, 98, 75);
    Bullet.getComponent<TransformComponent>().velocity.x = 3;
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

bool Game::checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    return rectA.x < rectB.x + rectB.w &&
        rectA.x + rectA.w > rectB.x &&
        rectA.y < rectB.y + rectB.h &&
        rectA.y + rectA.h > rectB.y;
}

void Game::Collision()
{
    // X? lý va ch?m
}

void Game::update()
{
    manager.refresh();
    manager.update();
    spawnEnemies();
    Collision();

    // Ki?m tra va ch?m gi?a các ??i t??ng
    playerRect = player.getComponent<SpriteComponent>().destRect;
    enemyRect1 = Enemy_Pawn1.getComponent<SpriteComponent>().destRect;
    enemyRect2 = Enemy_Pawn2.getComponent<SpriteComponent>().destRect;
    enemyRect3 = Enemy_Plane1.getComponent<SpriteComponent>().destRect;
    enemyRect4 = Enemy_Plane2.getComponent<SpriteComponent>().destRect;
    bulletshoot = Bullet.getComponent<SpriteComponent>().destRect;

    if (checkCollision(playerRect, enemyRect1))
        std::cout << "Touching Pawn 1" << std::endl;
    if (checkCollision(playerRect, enemyRect2))
        std::cout << "Touching Pawn 2" << std::endl;
    if (checkCollision(playerRect, enemyRect3))
        std::cout << "Touching Plane 1" << std::endl;
    if (checkCollision(playerRect, enemyRect4))
        std::cout << "Touching Plane 2" << std::endl;
    if (checkCollision(playerRect, bulletshoot))
        std::cout << "You died!!!!" << std::endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    // V? background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // V? b?n ??
    map->DrawMap();

    // V? sprite và các thành ph?n khác
    manager.draw();

    // C?p nh?t màn hình
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    Mix_HaltMusic(); // D?ng nh?c n?n tr??c khi gi?i phóng b? nh?
    Mix_CloseAudio(); // ?óng âm thanh
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
