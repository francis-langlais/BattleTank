#pragma once
#include "Game.h"
#include "Vector2D.h"

class Map
{
public:
    Map();
    ~Map();

    void DrawMap(int X, int Y);

    static SDL_Texture* MapTexture;

private:

    SDL_Rect srcTileRect, dstTileRect, srcMapRect, dstMapRect;

    SDL_Texture* bottomRight;
    SDL_Texture* bottomLeft;
    SDL_Texture* topRight;
    SDL_Texture* topLeft;
    SDL_Texture* top;
    SDL_Texture* bottom;
    SDL_Texture* left;
    SDL_Texture* right;
    SDL_Texture* middle;


};
