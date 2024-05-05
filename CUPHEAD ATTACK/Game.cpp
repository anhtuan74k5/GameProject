#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
//#include "Vector2D.h"
#include "Header.h"
#include <SDL_mixer.h> // Thêm th? vi?n SDL_mixer
#include "KeyboardController.h"
#include <cstdlib>
#include <ctime>
#include "Additional.h"


SDL_Rect playerRect;
SDL_Rect enemyRect1;
SDL_Rect enemyRect2;
SDL_Rect enemyRect3;
SDL_Rect enemyRect4;
SDL_Rect bulletRect;

Game::Game()
{}
Game::~Game()
{}

void Game::spawnEnemies()
{
    srand(time(NULL));
    // Bi?n th?i gian ?? tính th?i gian ?ã trôi qua t? l?n spawn cu?i cùng
    static Uint32 lastSpawnTime = SDL_GetTicks();

    // Th?i gian gi?a các l?n spawn (1 giây)
    const Uint32 spawnInterval = 3000;

    // Th?i gian hi?n t?i
    Uint32 currentTime = SDL_GetTicks();

    // N?u ?ã ?? th?i gian cho m?t l?n spawn m?i
    if (currentTime - lastSpawnTime >= spawnInterval)
    {
        // Reset th?i gian spawn cu?i cùng
        lastSpawnTime = currentTime;

        // Logic ?? t?o ra các ??i t??ng m?i ? ?ây...
        // Ví d?:
        srand(time(NULL));
        int randomNumber = rand() % 100;
        std::cout << randomNumber << std::endl;
        if (randomNumber % 2 == 0 || randomNumber % 10 == 1 || randomNumber % 10 == 3 || randomNumber % 10 == 5 || randomNumber % 10 == 7 || randomNumber % 10 == 9)
        {
            Enemy_Plane1.addComponent<TransformComponent>(-(rand() % 200), 80);
            Enemy_Plane2.addComponent<TransformComponent>(1000, 150);
            Enemy_Pawn1.addComponent<TransformComponent>(-(rand() % 200) - rand() % 1000, 350);
            Enemy_Pawn2.addComponent<TransformComponent>(1000, 350);
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
}


void Game::spawnBullet()
{
    int bulletFlag;
    // Load âm thanh bullet.wav
    Mix_Chunk* bulletSound = Mix_LoadWAV("assets/bullet.wav");
    if (!bulletSound) {
        std::cerr << "Failed to load bullet sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    // Phát âm thanh
    Mix_PlayChannel(-1, bulletSound, 0);

    std::string bulletImage = "";

    int playerDirection;
    //let playerDirection equals to the direction of the player from KeyboardController.h
    playerDirection = player.getComponent<KeyboardController>().getDirection();
    if (playerDirection == 3) { // H??ng sang ph?i (3)
        bulletImage = "assets/bulletLtoR.png";
        bulletFlag = 3; //x
    }
    else if (playerDirection == 2) { // H??ng sang trái (2)
        bulletImage = "assets/bulletRtoL.png";
        bulletFlag = -3;//x
    }
    else if (playerDirection == 1) {
        bulletImage = "assets/bulletUP.png";
        bulletFlag = -3; //y
    }
    else
    {
        bulletImage = "";
		bulletFlag = 0; //y
    }
 

    // T?o viên ??n t?i v? trí c?a ng??i ch?i
    if (playerDirection != 1)
    {
        Bullet.addComponent<TransformComponent>(player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y - 18);
        Bullet.addComponent<SpriteComponent>(bulletImage.c_str(), 4, 100, 155, 98, 75);
        Bullet.getComponent<TransformComponent>().velocity.x = bulletFlag; // ??t v?n t?c theo h??ng c?a ??n
    }
    else
    {
        Bullet.addComponent<TransformComponent>(player.getComponent<TransformComponent>().position.x + 20, player.getComponent<TransformComponent>().position.y - 30);
		Bullet.addComponent<SpriteComponent>(bulletImage.c_str(), 4, 100, 155, 98, 75);
		Bullet.getComponent<TransformComponent>().velocity.y = bulletFlag; // ??t v?n t?c theo h??ng c?a ??n
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

            // T?o viên ??n và thêm vào danh sách qu?n lý
            auto& bullet = manager.addEntity();
            bullet.addComponent<TransformComponent>(Enemy_Plane1.getComponent<TransformComponent>().position.x, Enemy_Plane1.getComponent<TransformComponent>().position.y);
            bullet.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
            bullet.getComponent<TransformComponent>().velocity.y = 3; // ??t v?n t?c theo h??ng c?a ??n
        }
    }
    if (randomChance % 10 == 2 || randomChance % 10 == 3 || randomChance % 10 == 6 || randomChance % 10 == 8 || randomChance % 10 == 0)
    {
        if (currentTime - Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime >= bulletInterval)
        {
            // Reset th?i gian b?n ??n
            Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime = currentTime;

            // T?o viên ??n và thêm vào danh sách qu?n lý
            auto& bullet = manager.addEntity();
            bullet.addComponent<TransformComponent>(Enemy_Plane2.getComponent<TransformComponent>().position.x, Enemy_Plane2.getComponent<TransformComponent>().position.y);
            bullet.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
            bullet.getComponent<TransformComponent>().velocity.y = 3; // ??t v?n t?c theo h??ng c?a ??n
        }
    }
}






void Game::handleEvents()
{
    SDL_PollEvent(&event);
    Additional::pauseGame(event); // G?i ph??ng th?c pauseGame t? file Additional.h

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_f:
            // B?n viên ??n khi nh?n phím F
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
    // X? lý va ch?m
}

void Game::update()
{
    if (!Additional::isGamePaused) {
        manager.refresh();
        manager.update();
        spawnEnemies();
       spawnEnemyBullets();
        Collision();



        // Ki?m tra va ch?m gi?a các ??i t??ng
        playerRect = player.getComponent<SpriteComponent>().destRect;
        enemyRect1 = Enemy_Pawn1.getComponent<SpriteComponent>().destRect;
        enemyRect2 = Enemy_Pawn2.getComponent<SpriteComponent>().destRect;
        enemyRect3 = Enemy_Plane1.getComponent<SpriteComponent>().destRect;
        enemyRect4 = Enemy_Plane2.getComponent<SpriteComponent>().destRect;
        bulletRect = Bullet.hasComponent<SpriteComponent>() ? Bullet.getComponent<SpriteComponent>().destRect : SDL_Rect();

        if (checkCollision(playerRect, enemyRect1))
            std::cout << "Va cham voi Pawn 1" << std::endl;
        if (checkCollision(playerRect, enemyRect2))
            std::cout << "Va cham voi Pawn 2" << std::endl;
        if (checkCollision(playerRect, enemyRect3))
            std::cout << "Va cham voi Plane 1" << std::endl;
        if (checkCollision(playerRect, enemyRect4))
            std::cout << "Va cham voi Plane 2" << std::endl;
        if (checkCollision(bulletRect, enemyRect1) || checkCollision(bulletRect, enemyRect2) || checkCollision(bulletRect, enemyRect3) || checkCollision(bulletRect, enemyRect4))
            std::cout << "Ban trung muc tieu!" << std::endl;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    // V? background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // V? b?n ??
    map->DrawMap();

    // V? sprite và các thành ph?n khác n?u trò ch?i không b? t?m d?ng
    if (!Additional::isGamePaused) {
        manager.draw();
    }
    Additional::renderHeart(renderer, 3);

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
