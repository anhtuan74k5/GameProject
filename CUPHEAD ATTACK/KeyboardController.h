#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"
#include "Header.h"
#include <SDL_mixer.h> // Thêm th? vi?n SDL_mixer

class KeyboardController : public Component
{
public:
    TransformComponent* transform;
    float gravity;
    bool musicPlaying;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        musicPlaying = false; // Kh?i t?o bi?n ki?m tra tr?ng thái nh?c
    }

    void update() override
    {
        gravity = 0.1;

        TransformComponent& playerTransform = entity->getComponent<TransformComponent>();

        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = -4;
                entity->getComponent<SpriteComponent>().setTex("assets/Jump_Sprite.png");
                break;
            case SDLK_a:
                transform->velocity.x = -4;
                entity->getComponent<SpriteComponent>().setTex("assets/RunLeft_Sprite.png");

                // Phát nh?c n?n
                if (!musicPlaying) {
                    Mix_Music* backgroundMusic = Mix_LoadMUS("assets/run.wav");
                    if (!backgroundMusic) {
                        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    }
                    else {
                        Mix_PlayMusic(backgroundMusic, -1);
                        musicPlaying = true; // ??t c? ?? ch? ra r?ng nh?c ?ã ???c phát
                    }
                }
                break;
            case SDLK_d:
                transform->velocity.x = 4;
                entity->getComponent<SpriteComponent>().setTex("assets/RunRight_Sprite.png");

                // Phát nh?c n?na
                if (!musicPlaying) {
                    Mix_Music* backgroundMusic = Mix_LoadMUS("assets/run.wav");
                    if (!backgroundMusic) {
                        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    }
                    else {
                        Mix_PlayMusic(backgroundMusic, -1);
                        musicPlaying = true; // ??t c? ?? ch? ra r?ng nh?c ?ã ???c phát
                    }
                }
                break;
            case SDLK_s:
                transform->velocity.y = 4;
                break;
            default:
                break;
            }
        }

        // D?ng nh?c n?n khi nh? phím A ho?c D
        if (Game::event.type == SDL_KEYUP && (Game::event.key.keysym.sym == SDLK_a || Game::event.key.keysym.sym == SDLK_d))
        {
            Mix_HaltMusic(); // D?ng nh?c n?n
            musicPlaying = false; // ??t l?i c? nh?c ?ã phát v? false
        }

        if (playerTransform.position.y >= 350)
        {
            transform->velocity.y = 0;
        }
        else
        {
            transform->velocity.y += gravity;
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/IdleLeft_Sprite.png");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");
                break;
            default:
                break;
            }
        }
    }
};
