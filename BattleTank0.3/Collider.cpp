//
// Created by eee466 on 21/05/19.
//

#include "Collider.h"

BoxCollider::BoxCollider(int size) {

    type = BOX;
    collider = {0, 0, size, size};
}


CircleCollider::CircleCollider(int rad, Vector2D<int> pos) {

    type = CIRCLE;
    radius = rad;
    position = pos;
}

