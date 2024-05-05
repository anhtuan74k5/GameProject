#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "SpriteComponent.h"

class BulletController : public Component
{
public:
    void init() override {}
    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_SPACE:
            {
                Entity& bullet = Game::manager.addEntity();
                bullet.addComponent<TransformComponent>(/* X và Y t??ng ?ng v?i v? trí ban ??u c?a ??n */);
                bullet.addComponent<SpriteComponent>("assets/bulletUP.png", 1, /* Chi?u r?ng và chi?u cao c?a ??n */);
                bullet.getComponent<TransformComponent>().velocity.x = /* T?c ?? di chuy?n c?a ??n theo tr?c X */;
                bullet.getComponent<TransformComponent>().velocity.y = /* T?c ?? di chuy?n c?a ??n theo tr?c Y */;
                break;
            }
            }
        }
    }
};