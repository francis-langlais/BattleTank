//
// Created by eee466 on 11/06/19.
//
#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"

class TileComponent : public Component
{
public:

    SDL_Texture * texture;
    SDL_Rect srcRect, destRect;
    Vector2D<int> position;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
    {
        texture = Game::assets->GetTexture(id);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        position.x = xpos;
        position.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }

    void update() override
    {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, 0, SDL_FLIP_NONE);
    }
};