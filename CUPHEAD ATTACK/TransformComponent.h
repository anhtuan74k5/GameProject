#pragma once
//#include "Components.h"
#include "ECS.h"
#include "Vector2D.h" // Include the header file for Vector2D

class TransformComponent : public Component
{
public:
    Vector2D position; // Declare the position variable of type Vector2D
    Vector2D velocity;

    int width;
    int height;
    int screenWidth;
    int screenHeight;

    int speed = 3;

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

    bool isOffScreen() const
    {

    return (position.x < -(this -> width) || position.y < -(this -> height) || position.x > this -> screenWidth || position.y > this -> screenHeight);


    }

};
