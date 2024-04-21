#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"
#include "Header.h"

class KeyboardController : public Component
{
public:
    TransformComponent* transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }
    //player.addComponent<SpriteComponent>("assets/Idle_Sprite.png", 4, 100, 155, 98, 75);
    //player.addComponent<SpriteComponent>("assets/RunLeft_Sprite.png", 4, 100, 155, 135, 75);
    //player.addComponent<SpriteComponent>("assets/RunRight_Sprite.png", 4, 100, 155, 135, 75);
    //player.addComponent<SpriteComponent>("assets/Jump_Sprite.png", 4, 100, 109, 82, 50);
    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN) //if a key is pressed
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = -2;
                entity->getComponent<SpriteComponent>().setTex("assets/Jump_Sprite.png");
                break;
            case SDLK_a:
                transform->velocity.x = -2;
                entity->getComponent<SpriteComponent>().setTex("assets/RunLeft_Sprite.png");
                break;
            case SDLK_d:
                transform->velocity.x = 2;
                entity->getComponent<SpriteComponent>().setTex("assets/RunRight1_Sprite.png");
                break;
            case SDLK_s:
                transform->velocity.y = 2;
                break;
            default:
                break;
            }
        }
        if (Game::event.type == SDL_KEYUP) //if a key is released
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                // Switch back to Idle_Sprite when 'A' key is released
                entity->getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                // Switch back to Idle_Sprite when 'D' key is released
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
