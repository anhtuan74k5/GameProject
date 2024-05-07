#pragma once

#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"

class Bullet : public Component
{
private:
    TransformComponent* transform = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect srcRect = {};
    SDL_Rect destRect = {};

    int speed = 5; // T?c ?? di chuy?n c?a ??n

public:
    Bullet() = default;

    Bullet(const char* path, int speed)
    {
        this->speed = speed;
        setTex(path);
    }

    ~Bullet()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = destRect.w = 16; 
        srcRect.h = destRect.h = 16;
    }

    void update() override
    {
        transform->position.y -= speed;

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};
