#pragma once

#include "ECS.h"
#include "Vector2D.h" 

class TransformComponent : public Component
{
public:
    Vector2D position; 
    Vector2D velocity;

    int width;
    int height;
    int screenWidth;
    int screenHeight;
    int speed = 3;
    Uint32 lastBulletTime = 0;

    TransformComponent()
    {
        position.x = 0;
        position.y = 0;
    }

    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }
    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
   

};
