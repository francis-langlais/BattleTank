//
// Created by eee466 on 01/05/19.
//
#pragma once


#include "Components.h"
#include "../Vector2D.h"
#include "../EngineMath.h"

class TransformComponent : public Component
{
public:
    Vector2D<int> position;
    Vector2D<float> velocity;

    float velTest = 0;

    int height = 32;
    int width = 32;
    int scale = 1;

    int rotation = 0;
    int RotAngle = 3;
    int RotSpeed = 0;

    int speed = 10;

    bool blocked = false;

    TransformComponent()
    {
        position = Vector2D<int>();
    }

    TransformComponent(int sc)
    {
        position = Vector2D<int>();
        scale = sc;
    }

    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int h, int w, int sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override
    {
        velocity = Vector2D<float>();
    }

    void update() override
    {
        rotation += RotAngle * RotSpeed;

        Vector2D<float> moveEntity = {1,1};

        moveEntity.x = 1 * cos(EngineMath::DegreeToRad(rotation - 90));
        moveEntity.y = 1 * sin(EngineMath::DegreeToRad(rotation - 90));

        moveEntity = Normal(moveEntity);

        position.x += static_cast<int>(velTest * speed * moveEntity.x);
        position.y += static_cast<int>(velTest * speed * moveEntity.y);
    }
};
