//
// Created by eee466 on 08/05/19.
//

#pragma once


#include <SDL_rect.h>
#include "Vector2D.h"
#include <iostream>

enum ColliderType
{
    BOX,
    CIRCLE
};

class Collider
{
public:
    ColliderType type;
};

class BoxCollider : public Collider
{
public:

    SDL_Rect collider;

    BoxCollider(int size);

};

class CircleCollider : public Collider
{
public:
    int radius;
    Vector2D<int> position;

    CircleCollider(int rad, Vector2D<int> pos);

};
