#include "Map.h"
#include "TextureManager.h"
#include "EngineMath.h"

/*
 *  0 = Bottom Right corner
 *  1 = Bottom Left Corner
 *  2 = Top Right Corner
 *  3 = Top Left Corner
 *  4 = Top
 *  5 = Bottom
 *  6 = Left
 *  7 = Right
 *  8 = Middle
 */

Map::Map()
{

    bottomRight = TextureManager::LoadTexture("Ressources/Image/Tiles/Bottom_Right.png");
    bottomLeft = TextureManager::LoadTexture("Ressources/Image/Tiles/Bottom_Left.png");
    topRight = TextureManager::LoadTexture("Ressources/Image/Tiles/Top_Right.png");
    topLeft = TextureManager::LoadTexture("Ressources/Image/Tiles/Top_Left.png");
    top = TextureManager::LoadTexture("Ressources/Image/Tiles/Top.png");
    bottom = TextureManager::LoadTexture("Ressources/Image/Tiles/Bottom.png");
    left = TextureManager::LoadTexture("Ressources/Image/Tiles/Left.png");
    right = TextureManager::LoadTexture("Ressources/Image/Tiles/Right.png");
    middle = TextureManager::LoadTexture("Ressources/Image/Tiles/Middle.png");

    srcTileRect = { 0, 0, 256, 256 };
    dstTileRect = { 0, 0, TILE_SIZE, TILE_SIZE };

    srcMapRect = {0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT};
    dstMapRect = {0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT};

}

Map::~Map()
{
    SDL_DestroyTexture(bottomRight);
    SDL_DestroyTexture(bottomLeft);
    SDL_DestroyTexture(topRight);
    SDL_DestroyTexture(topLeft);
    SDL_DestroyTexture(top);
    SDL_DestroyTexture(bottom);
    SDL_DestroyTexture(left);
    SDL_DestroyTexture(right);
    SDL_DestroyTexture(middle);
}

void Map::DrawMap(int X, int Y) {

    float Tile_X = EngineMath::PixelToTile(X);
    float Tile_Y = EngineMath::PixelToTile(Y);

    for(int x = static_cast<int>(Tile_X); x <= static_cast<int>(Tile_X) + 16; x++)
    {
        for(int y = static_cast<int>(Tile_Y); y <= static_cast<int>(Tile_Y) + 16; y++)
        {
            dstTileRect.x = EngineMath::TileToPixel(x - Tile_X);
            dstTileRect.y = EngineMath::TileToPixel(y - Tile_Y);
            if(y == 0)
            {
                if(x == 0)
                {
                    SDL_RenderCopy(Game::Renderer, topLeft, NULL, &dstTileRect);
                } else if(x == NUM_TILE - 1)
                {
                    SDL_RenderCopy(Game::Renderer, topRight, NULL, &dstTileRect);
                } else
                {
                    SDL_RenderCopy(Game::Renderer, top, NULL, &dstTileRect);
                }
            } else if(y == NUM_TILE - 1)
            {
                if(x == 0)
                {
                    SDL_RenderCopy(Game::Renderer, bottomLeft, NULL, &dstTileRect);
                } else if(x == NUM_TILE - 1)
                {
                    SDL_RenderCopy(Game::Renderer, bottomRight, NULL, &dstTileRect);
                } else
                {
                    SDL_RenderCopy(Game::Renderer, bottom, NULL, &dstTileRect);
                }
            } else{
                if(x == 0)
                {
                    SDL_RenderCopy(Game::Renderer, left, NULL, &dstTileRect);
                } else if(x == NUM_TILE - 1)
                {
                    SDL_RenderCopy(Game::Renderer, right, NULL, &dstTileRect);
                } else
                {
                    SDL_RenderCopy(Game::Renderer, middle, NULL, &dstTileRect);
                }

            }


        }
    }
}
