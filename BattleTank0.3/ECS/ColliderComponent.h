//
// Created by eee466 on 08/05/19.
//

#pragma once

#include <string>
#include "../Collider.h"
#include "Components.h"


class ColliderComponent : public Component
{
public:
    Collider* mCollider;
    std::string tag;
    TransformComponent* transform;

    ColliderComponent(std::string tag, ColliderType type, int size)
    {
        this->tag = tag;

        switch (type){
            case BOX:
                mCollider = new BoxCollider(size);
                break;
            case CIRCLE:
                mCollider = new CircleCollider(size, {0,0});
                break;
        }
    }
    ~ColliderComponent()
    {
        free(mCollider);
    }

    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        switch (mCollider->type) {
            BoxCollider* boxCol;
            CircleCollider* circleCol;
            case BOX:
                boxCol = static_cast<BoxCollider*>(mCollider);
                boxCol->collider.x = static_cast<int>(transform->position.x);
                boxCol->collider.y = static_cast<int>(transform->position.y);
                boxCol->collider.w = transform->width * transform->scale;
                boxCol->collider.h = transform->height * transform->scale;
                break;
            case CIRCLE:
                circleCol = static_cast<CircleCollider*>(mCollider);
                circleCol->position = transform->position;
                circleCol->radius = transform->height / 2;
                break;
        }
    }


};
