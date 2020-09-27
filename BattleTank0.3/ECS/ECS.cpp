//
// Created by eee466 on 13/05/19.
//

#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}