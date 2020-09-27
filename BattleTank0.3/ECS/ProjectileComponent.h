//
// Created by eee466 on 13/05/19.
//
#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int rng, int sp, Vector2D<float> vel) : range(rng), speed(sp), velocity(vel)
    {}
    ~ProjectileComponent()
    {}

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        transform->velocity = velocity;
    }

    void update() override
    {
        distance += speed;

        if (distance > range)
        {
            std::cout << "Out of Range" << std::endl;
            entity->destroy();
        }
        /*
        else if (transform->position.x > MAP_SIZE ||
                 transform->position.x < 0 ||
                 transform->position.y > MAP_SIZE ||
                 transform->position.y < 0)
        {
            std::cout << "Out of bounds!" << std::endl;
            entity->destroy();
        }*/
    }

private:

    TransformComponent* transform;

    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D<float> velocity;


};