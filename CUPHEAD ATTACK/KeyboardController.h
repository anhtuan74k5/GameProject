#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"
#include "Header.h"
#include <SDL_mixer.h> 
class KeyboardController : public Component {
private:
    Game* game;
public:
    TransformComponent* transform;
    bool musicPlaying;  
    int direction;

    void setGame(Game* gamePtr) {
        game = gamePtr;
	}


    int getDirection() const {
		return direction;
	}


  
    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        musicPlaying = false; 
        direction = 0;
    }

    void update() override {

        TransformComponent& playerTransform = entity->getComponent<TransformComponent>();

        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
                entity->getComponent<SpriteComponent>().setTex("assets/aimUP.png");
                direction = 1;  
                break;
            case SDLK_a:    
                if (playerTransform.position.x >= 0)
                    transform->velocity.x = -3;
                else if (playerTransform.position.x < 0)
                {
                    transform->velocity.x = 0;
                    transform->position.x = 0;
                }
                    entity->getComponent<SpriteComponent>().setTex("assets/RunLeft_Sprite.png");
                    direction = 2;
                
                break;
            case SDLK_d:
                if (playerTransform.position.x <= 1000) 
                    transform->velocity.x = 3;
                else if (playerTransform.position.x > 1000)
                {
                    transform->velocity.x = 0;
                    transform->position.x = 930;
                }
                    entity->getComponent<SpriteComponent>().setTex("assets/RunRight_Sprite.png");
                    direction = 3;
                
                break;
            case SDLK_f:
                    game->spawnBullet();
                break;


            default:
                break;
            }
        }

      
        if (Game::event.type == SDL_KEYUP && (Game::event.key.keysym.sym == SDLK_a || Game::event.key.keysym.sym == SDLK_d)) {
            Mix_HaltMusic(); 
            musicPlaying = false; 
        }

 

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
                transform->velocity.y = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/aimUP.png");
                direction = 1;
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/IdleLeft_Sprite.png");
                direction = 2;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                entity->getComponent<SpriteComponent>().setTex("assets/Idle_Sprite.png");
                direction = 3;
                break;

            default:
                break;
            }
        }
    }
};
