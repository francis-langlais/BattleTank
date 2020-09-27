//
// Created by eee466 on 09/05/19.
//

#pragma once

#include <SDL_rect.h>

class ColliderComponent;

class CollisionDetection {

public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

    static bool OBB(const ColliderComponent &colA, const ColliderComponent &colB);

    static bool CC(const ColliderComponent &colA, const ColliderComponent &colB);
};
