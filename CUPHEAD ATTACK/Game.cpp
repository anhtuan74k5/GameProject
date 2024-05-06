#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Header.h"
#include <SDL_mixer.h>
#include "KeyboardController.h"
#include <cstdlib>
#include <ctime>
#include "Additional.h"
#include <SDL_ttf.h>

SDL_Rect playerRect;
SDL_Rect enemyRect1;
SDL_Rect enemyRect2;
SDL_Rect enemyRect3;
SDL_Rect enemyRect4;
SDL_Rect bulletRect;
SDL_Rect EnemyBulletRect;

Game::Game() {}
Game::~Game() {}

void Game::spawnEnemies()
{
    player.addComponent<TransformComponent>(500, 350);
    player.addComponent<SpriteComponent>("assets/Idle_Sprite.png", 4, 100, 155, 98, 75);
    player.addComponent<KeyboardController>();

    Enemy_Plane1.addComponent<TransformComponent>(-100, 80);
    Enemy_Plane1.addComponent<SpriteComponent>("assets/Enemy_PlaneRight.png", 4, 100, 99, 112, 75);
    Enemy_Plane1.getComponent<TransformComponent>().velocity.x = 1;
    Enemy_Plane1.getComponent<TransformComponent>().lastBulletTime = 0; // Kh?i t?o lastBulletTime

    Enemy_Plane2.addComponent<TransformComponent>(1500, 150);
    Enemy_Plane2.addComponent<SpriteComponent>("assets/Enemy_PlaneLeft.png", 4, 100, 99, 112, 75);
    Enemy_Plane2.getComponent<TransformComponent>().velocity.x = -1;
    Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime = 0; // Kh?i t?o lastBulletTime

    Enemy_Pawn1.addComponent<TransformComponent>(-500, 350);
    Enemy_Pawn1.addComponent<SpriteComponent>("assets/Enemy_PawnRight.png", 4, 100, 102, 127, 75);
    Enemy_Pawn1.getComponent<TransformComponent>().velocity.x = 1;

    Enemy_Pawn2.addComponent<TransformComponent>(1100, 350);
    Enemy_Pawn2.addComponent<SpriteComponent>("assets/Enemy_PawnLeft.png", 4, 100, 102, 127, 75);
    Enemy_Pawn2.getComponent<TransformComponent>().velocity.x = -1;
}

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
    else
        isRunning = false;

    LoadBackground("assets/background.png");

    map = new Map();

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL Audio initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_Music* backgroundMusic = Mix_LoadMUS("assets/rainforestambience.wav");
    if (!backgroundMusic)
    {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    spawnEnemies();
}

void Game::spawnBullet()
{
    int bulletFlag;
    Mix_Chunk* bulletSound = Mix_LoadWAV("assets/bullet.wav");
    if (!bulletSound)
    {
        std::cerr << "Failed to load bullet sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_PlayChannel(-1, bulletSound, 0);

    std::string bulletImage = "";

    int playerDirection;
    playerDirection = player.getComponent<KeyboardController>().getDirection();
    if (playerDirection == 3)
    {
        bulletImage = "assets/bulletLtoR.png";
        bulletFlag = 3;
    }
    else if (playerDirection == 2)
    {
        bulletImage = "assets/bulletRtoL.png";
        bulletFlag = -3;
    }
    else if (playerDirection == 1)
    {
        bulletImage = "assets/bulletUP.png";
        bulletFlag = -3;
    }
    else
    {
        bulletImage = "";
        bulletFlag = 0;
    }

    if (playerDirection != 1)
    {
        Bullet.addComponent<TransformComponent>(player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y - 18);
        Bullet.addComponent<SpriteComponent>(bulletImage.c_str(), 4, 100, 155, 98, 75);
        Bullet.getComponent<TransformComponent>().velocity.x = bulletFlag;
    }
    else
    {
        Bullet.addComponent<TransformComponent>(player.getComponent<TransformComponent>().position.x + 20, player.getComponent<TransformComponent>().position.y - 30);
        Bullet.addComponent<SpriteComponent>(bulletImage.c_str(), 4, 100, 155, 98, 75);
        Bullet.getComponent<TransformComponent>().velocity.y = bulletFlag;
    }
}

void Game::spawnEnemyBullets()
{
    int randomChance = rand() % 10;
    const Uint32 bulletInterval = 1000;
    Uint32 currentTime = SDL_GetTicks();

    if (randomChance % 10 == 1 || randomChance % 10 == 3 || randomChance % 10 == 5 || randomChance % 10 == 7 || randomChance % 10 == 9)
    {
        if (currentTime - Enemy_Plane1.getComponent<TransformComponent>().lastBulletTime >= bulletInterval)
        {
            Enemy_Plane1.getComponent<TransformComponent>().lastBulletTime = currentTime;

            auto& enemybullet = manager.addEntity();
            enemybullet.addComponent<TransformComponent>(Enemy_Plane1.getComponent<TransformComponent>().position.x, Enemy_Plane1.getComponent<TransformComponent>().position.y);
            enemybullet.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
            enemybullet.getComponent<TransformComponent>().velocity.y = 3;
            enemybullet.getComponent<TransformComponent>().velocity.x = 1;
            //Handle the collision between the bullet and the player
            EnemyBulletRect = enemybullet.getComponent<SpriteComponent>().destRect;

        }
    }
    if (randomChance % 10 == 2 || randomChance % 10 == 3 || randomChance % 10 == 6 || randomChance % 10 == 8 || randomChance % 10 == 0)
    {
        if (currentTime - Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime >= bulletInterval)
        {
            Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime = currentTime;

            auto& enemybullet = manager.addEntity();
            enemybullet.addComponent<TransformComponent>(Enemy_Plane2.getComponent<TransformComponent>().position.x, Enemy_Plane2.getComponent<TransformComponent>().position.y);
            enemybullet.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
            enemybullet.getComponent<TransformComponent>().velocity.y = 3;
        }
    }
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    Additional::pauseGame(event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_f:
            spawnBullet();
            break;
        default:
            break;
        }
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
    // Handle collision
}

void Game::update()
{
    if (!Additional::isGamePaused)
    {
        manager.refresh();
        manager.update();
        //spawnEnemies();
        spawnEnemyBullets();
        //Collision();

        playerRect = player.getComponent<SpriteComponent>().destRect;
        enemyRect1 = Enemy_Pawn1.hasComponent<SpriteComponent>() ? Enemy_Pawn1.getComponent<SpriteComponent>().destRect : SDL_Rect();
        enemyRect2 = Enemy_Pawn2.hasComponent<SpriteComponent>() ? Enemy_Pawn2.getComponent<SpriteComponent>().destRect : SDL_Rect();
        enemyRect3 = Enemy_Plane1.hasComponent<SpriteComponent>() ? Enemy_Plane1.getComponent<SpriteComponent>().destRect : SDL_Rect();
        enemyRect4 = Enemy_Plane2.hasComponent<SpriteComponent>() ? Enemy_Plane2.getComponent<SpriteComponent>().destRect : SDL_Rect();

        bulletRect = Bullet.hasComponent<SpriteComponent>() ? Bullet.getComponent<SpriteComponent>().destRect : SDL_Rect();

        if (checkCollision(playerRect, enemyRect1))
        {
            std::cout << "Va cham voi Pawn 1" << std::endl;
            numberHeart--;
        }
        if (checkCollision(playerRect, enemyRect2))
        {
            std::cout << "Va cham voi Pawn 2" << std::endl;
            numberHeart--;
		}

        if (checkCollision(playerRect, EnemyBulletRect))
        {
            numberHeart--;
        }

        bool checkBullet = false;

        if (checkCollision(bulletRect, enemyRect1))
        {
            std::cout << "Ban trung Pawn 1!" << std::endl;
            Enemy_Pawn1.getComponent<TransformComponent>().position.x = -100;
            Enemy_Pawn1.getComponent<TransformComponent>().position.y = 350;
            checkBullet = true;
        }
        if (checkCollision(bulletRect, enemyRect2))
        {
			std::cout << "Ban trung Pawn 2!" << std::endl;
			//Enemy_Pawn2.destroy(); // Destroy Pawn 2
			Enemy_Pawn2.getComponent<TransformComponent>().position.x = 900;
			Enemy_Pawn2.getComponent<TransformComponent>().position.y = 350;
            checkBullet = true;
		}

        if (checkCollision(bulletRect, enemyRect3))
        {
			std::cout << "Ban trung Plane 1!" << std::endl;
			//Enemy_Plane1.destroy(); // Destroy Plane 1
			Enemy_Plane1.getComponent<TransformComponent>().position.x = 0;
			Enemy_Plane1.getComponent<TransformComponent>().position.y = 80;
            checkBullet = true;

		}

        if (checkCollision(bulletRect, enemyRect4))
        {
            std::cout << "Ban trung Plane 2!" << std::endl;
            //Enemy_Plane2.destroy(); // Destroy Plane 2
            Enemy_Plane2.getComponent<TransformComponent>().position.x = 900;
            Enemy_Plane2.getComponent<TransformComponent>().position.y = 150;
            checkBullet = true;
        }

        if (checkBullet)
        {
			Bullet.getComponent<TransformComponent>().position.x = -100;
			Bullet.getComponent<TransformComponent>().position.y = -100;
		}

    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    map->DrawMap();

    if (!Additional::isGamePaused)
    {
        manager.draw();
    }
    Additional::renderHeart(renderer, numberHeart);

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
