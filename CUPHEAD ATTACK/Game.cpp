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
#include <fstream>



Game::Game() {}
Game::~Game() {}

void Game::spawnEntities()
{
  
    player.addComponent<TransformComponent>(450, 350);
    player.addComponent<SpriteComponent>("assets/Idle_Sprite.png", 4, 100, 155, 98, 75);
    player.addComponent<KeyboardController>();
    player.getComponent<KeyboardController>().setGame(this);


    Enemy_Plane1.addComponent<TransformComponent>(-100, 80);
    Enemy_Plane1.addComponent<SpriteComponent>("assets/Enemy_PlaneRight.png", 4, 100, 99, 112, 75);
    Enemy_Plane1.getComponent<TransformComponent>().velocity.x = 2;

    Enemy_Plane2.addComponent<TransformComponent>(1300, 150);
    Enemy_Plane2.addComponent<SpriteComponent>("assets/Enemy_PlaneLeft.png", 4, 100, 99, 112, 75);
    Enemy_Plane2.getComponent<TransformComponent>().velocity.x = -2;

    Enemy_Pawn1.addComponent<TransformComponent>(-500, 350);
    Enemy_Pawn1.addComponent<SpriteComponent>("assets/Enemy_PawnRight.png", 4, 100, 102, 127, 75);
    Enemy_Pawn1.getComponent<TransformComponent>().velocity.x = 1;

    Enemy_Pawn2.addComponent<TransformComponent>(1100, 350);
    Enemy_Pawn2.addComponent<SpriteComponent>("assets/Enemy_PawnLeft.png", 4, 100, 102, 127, 75);
    Enemy_Pawn2.getComponent<TransformComponent>().velocity.x = -1;

    EnemyBullet1.addComponent<TransformComponent>(-100, -100);
    EnemyBullet1.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
    EnemyBullet1.getComponent<TransformComponent>().velocity.y = 3;

    EnemyBullet2.addComponent<TransformComponent>(-100, -100);
    EnemyBullet2.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
    EnemyBullet2.getComponent<TransformComponent>().velocity.y = 3;

}

void Game::spawnEnemyBullets()
{
    srand(time(NULL));
    int randomChance = rand() % 10;
    const Uint32 bulletInterval = 1000;
    Uint32 currentTime = SDL_GetTicks();
    if (randomChance % 10 == 1 || randomChance % 10 == 3 || randomChance % 10 == 5 || randomChance % 10 == 7 || randomChance % 10 == 9)
    {
        if (currentTime - Enemy_Plane1.getComponent<TransformComponent>().lastBulletTime >= bulletInterval)
        {
            Enemy_Plane1.getComponent<TransformComponent>().lastBulletTime = currentTime;

            EnemyBullet1.getComponent<TransformComponent>().position.x = Enemy_Plane1.getComponent<TransformComponent>().position.x + 50;
            EnemyBullet1.getComponent<TransformComponent>().position.y = Enemy_Plane1.getComponent<TransformComponent>().position.y + 50;

            if (!EnemyBullet1.hasComponent<SpriteComponent>()) {
                EnemyBullet1.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
            }

            EnemyBullet1.getComponent<TransformComponent>().velocity.y = 3;
        }
    }
    if (randomChance % 10 == 2 || randomChance % 10 == 3 || randomChance % 10 == 6 || randomChance % 10 == 8 || randomChance % 10 == 0)
    {
        if (currentTime - Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime >= bulletInterval)
        {
            Enemy_Plane2.getComponent<TransformComponent>().lastBulletTime = currentTime;

            EnemyBullet2.getComponent<TransformComponent>().position.x = Enemy_Plane2.getComponent<TransformComponent>().position.x + 50;
            EnemyBullet2.getComponent<TransformComponent>().position.y = Enemy_Plane2.getComponent<TransformComponent>().position.y + 50;

            if (!EnemyBullet2.hasComponent<SpriteComponent>()) {
                EnemyBullet2.addComponent<SpriteComponent>("assets/EnemyBullet.png", 4, 100, 155, 98, 75);
            }

            EnemyBullet2.getComponent<TransformComponent>().velocity.y = 3;
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

     if (TTF_Init() == -1)
        {
			std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
			return;
		}

        isRunning = true;
    }
    else
        isRunning = false;

    std::ifstream file("assets/highest_score.txt");
    if (file.is_open()) {
        file >> highestScore;
        file.close();
    }

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

    Mix_Music* StartMusic = Mix_LoadMUS("assets/rainforestambience.wav");

    if (!StartMusic)
    {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        Mix_PlayMusic(StartMusic, -1);
    }



    spawnEntities();
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

    



    int playerDirection;
    playerDirection = player.getComponent<KeyboardController>().getDirection();
    if (playerDirection == 3)
    {
        bulletImage = "assets/bulletLtoR.png";
        bulletFlag = 5;     //xpos
    }
    else if (playerDirection == 2)
    {
        bulletImage = "assets/bulletRtoL.png";
        bulletFlag = -5;    //xpos
    }
    else if (playerDirection == 1)
    {
        bulletImage = "assets/bulletUP.png";
        bulletFlag = -5;    //ypos
    }
    else
    {
        bulletImage = "assets/bulletLtoR.png";;
        bulletFlag = 5;
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
        case SDLK_ESCAPE:
			isRunning = false;
			break;
        case SDLK_RETURN:
            if (!isGameStarted) 
                isGameStarted = true;

            if (isGameOver)
                prepareGame();
            if (Mix_PlayingMusic() != 0)
            {
                Mix_HaltMusic();
            }
            break;
        default:
            break;
        }
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
    // Handle collision
}

void Game::update()
{
    if (!isGameStarted || isGameOver || Additional::isGamePaused) {
        return;
    }
    if (!Additional::isGamePaused && !isGameOver)
    {
        manager.refresh();
        manager.update();
        spawnEnemyBullets();
        //Collision();
        if (numberHeart <= 0)
            isGameOver = true;

   

        playerRect = player.getComponent<SpriteComponent>().destRect;
        enemyRect1 = Enemy_Pawn1.hasComponent<SpriteComponent>() ? Enemy_Pawn1.getComponent<SpriteComponent>().destRect : SDL_Rect();
        enemyRect2 = Enemy_Pawn2.hasComponent<SpriteComponent>() ? Enemy_Pawn2.getComponent<SpriteComponent>().destRect : SDL_Rect();
        enemyRect3 = Enemy_Plane1.hasComponent<SpriteComponent>() ? Enemy_Plane1.getComponent<SpriteComponent>().destRect : SDL_Rect();
        enemyRect4 = Enemy_Plane2.hasComponent<SpriteComponent>() ? Enemy_Plane2.getComponent<SpriteComponent>().destRect : SDL_Rect();
   	    EnemyBulletRect1 = EnemyBullet1.hasComponent<SpriteComponent>() ? EnemyBullet1.getComponent<SpriteComponent>().destRect : SDL_Rect();
        EnemyBulletRect2 = EnemyBullet2.hasComponent<SpriteComponent>() ? EnemyBullet2.getComponent<SpriteComponent>().destRect : SDL_Rect();

        bulletRect = Bullet.hasComponent<SpriteComponent>() ? Bullet.getComponent<SpriteComponent>().destRect : SDL_Rect();

        if (checkCollision(playerRect, enemyRect1))
        {
            std::cout << "Va cham voi Pawn 1" << std::endl;
            numberHeart--;
            Enemy_Pawn1.getComponent<TransformComponent>().position.x = -700;
            Enemy_Pawn1.getComponent<TransformComponent>().position.y = 350;
        }

        if (checkCollision(playerRect, enemyRect2))
        {
            std::cout << "Va cham voi Pawn 2" << std::endl;
            numberHeart--;
            Enemy_Pawn2.getComponent<TransformComponent>().position.x = 1400;
            Enemy_Pawn2.getComponent<TransformComponent>().position.y = 350;
        }

        if (checkCollision(playerRect, EnemyBulletRect1))
        {
            numberHeart--;
           EnemyBullet1.getComponent<TransformComponent>().position.x = -100;
           EnemyBullet1.getComponent<TransformComponent>().position.y = -100;
        }
        if (checkCollision(playerRect, EnemyBulletRect2))
        {
            numberHeart--;
            EnemyBullet2.getComponent<TransformComponent>().position.x = -100;
            EnemyBullet2.getComponent<TransformComponent>().position.y = -100;
        }
        bool checkBullet = false;


        //Respawn
        if (Enemy_Plane1.getComponent<TransformComponent>().position.x >= 1200)
        {
			Enemy_Plane1.getComponent<TransformComponent>().position.x = -200;
		}
        if (Enemy_Plane2.getComponent<TransformComponent>().position.x <= -400)
        {
            Enemy_Plane2.getComponent<TransformComponent>().position.x = 1200;
        }

        if (checkCollision(bulletRect, enemyRect1))
        {
            std::cout << "Ban trung Pawn 1!" << std::endl;
            Enemy_Pawn1.getComponent<TransformComponent>().position.x = -600;
            Enemy_Pawn1.getComponent<TransformComponent>().position.y = 350;
            checkBullet = true;
            score++;
        }

        if (checkCollision(bulletRect, enemyRect2))
        {
			std::cout << "Ban trung Pawn 2!" << std::endl;
			Enemy_Pawn2.getComponent<TransformComponent>().position.x = 1300;
			Enemy_Pawn2.getComponent<TransformComponent>().position.y = 350;
            checkBullet = true;
            score++;
		}

        if (checkCollision(bulletRect, enemyRect3))
        {
			std::cout << "Ban trung Plane 1!" << std::endl;
			Enemy_Plane1.getComponent<TransformComponent>().position.x = -600;
			Enemy_Plane1.getComponent<TransformComponent>().position.y = 80;
            checkBullet = true;
            score++;
		}

        if (checkCollision(bulletRect, enemyRect4))
        {
            std::cout << "Ban trung Plane 2!" << std::endl;
            Enemy_Plane2.getComponent<TransformComponent>().position.x = 1400;
            Enemy_Plane2.getComponent<TransformComponent>().position.y = 150;
            checkBullet = true;
            score++;
        }

        if (checkBullet)
        {
			Bullet.getComponent<TransformComponent>().position.x = -100;
			Bullet.getComponent<TransformComponent>().position.y = -100;
		}

        if (score > highestScore) {
            highestScore = score;
        }

    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    if (!isGameStarted) {
        Additional::renderStartMenu(renderer);
    }
    else if (!isGameOver)
    {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        map->DrawMap();

        manager.draw();
        Additional::renderHeart(renderer, numberHeart);
        Additional::renderScore(renderer, score, 450, 25, 35, "SCORE");
        Additional::renderPauseMenu(renderer);
    }
    else
    {

        SDL_Surface* gameOverSurface = IMG_Load("assets/youlose.png");
        if (!gameOverSurface) {
            std::cerr << "Failed to load game over image: " << SDL_GetError() << std::endl;
        }
        else {
            SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
            if (!gameOverTexture) {
                std::cerr << "Failed to create game over texture: " << SDL_GetError() << std::endl;
            }
            else {
                SDL_Rect gameOverRect;
                gameOverRect.x = 0;
                gameOverRect.y = 0;
                gameOverRect.w = gameOverSurface->w;
                gameOverRect.h = gameOverSurface->h;
                SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
                SDL_DestroyTexture(gameOverTexture);
                Additional::renderScore(renderer, score, 350, 260, 45, "Current Score");
                Additional::renderScore(renderer, highestScore, 350, 330, 45, "Highest Score");
            }
            SDL_FreeSurface(gameOverSurface);
        }
    }

    SDL_RenderPresent(renderer);
}


void Game::saveHighestScoreToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << highestScore;
        file.close();
    }
    else {  
        std::cerr << "Unable to open file for saving highest score: " << filename << std::endl;
    }
}

void Game::prepareGame() {
	numberHeart = 3;
	score = 0;
	isGameOver = false;
	player.getComponent<TransformComponent>().position.x = 450;
	player.getComponent<TransformComponent>().position.y = 350;
    player.getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");

    
    player.getComponent<KeyboardController>().direction = 0;
    player.getComponent<TransformComponent>().velocity.x = 0;
    player.getComponent<TransformComponent>().velocity.y = 0;

	Enemy_Pawn1.getComponent<TransformComponent>().position.x = -500;
	Enemy_Pawn1.getComponent<TransformComponent>().position.y = 350;
	Enemy_Pawn2.getComponent<TransformComponent>().position.x = 1100;
	Enemy_Pawn2.getComponent<TransformComponent>().position.y = 350;
	Enemy_Plane1.getComponent<TransformComponent>().position.x = -100;
	Enemy_Plane1.getComponent<TransformComponent>().position.y = 80;
	Enemy_Plane2.getComponent<TransformComponent>().position.x = 1300;
	Enemy_Plane2.getComponent<TransformComponent>().position.y = 150;

	saveHighestScoreToFile("highest_score.txt");
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
