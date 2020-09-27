//
// Created by eee466 on 25/06/19.
//

#include "MiniMap.h"
#include "Map.h"
#include "Game.h"
#include "TextureManager.h"

MiniMap::MiniMap() {

    rightspace = SCREEN_WIDTH - SCREEN_HEIGHT;

    std::cout << "RightSpace = " << rightspace << std::endl;

    MiniMapTexture = SDL_CreateTexture(Game::Renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, rightspace, rightspace);
    SDL_SetRenderTarget(Game::Renderer, MiniMapTexture);
    SDL_RenderClear(Game::Renderer);
    SDL_SetRenderTarget(Game::Renderer, NULL);

    dstRect = {SCREEN_HEIGHT, SCREEN_HEIGHT - rightspace, rightspace, rightspace};
    squareRect = {0, 0, (rightspace - (2 * EDGE_PADDING + (NUMBER_OF_SQUARE - 1) * MINIMAP_PADDING)) / NUMBER_OF_SQUARE, (rightspace - (2 * EDGE_PADDING + (NUMBER_OF_SQUARE - 1) * MINIMAP_PADDING)) / NUMBER_OF_SQUARE};

    for (int i = 0; i < NUMBER_OF_SQUARE; i++) {
        for (int j = 0; j < NUMBER_OF_SQUARE; j++) {
            miniMap[i][j] = 0;
            miniMapDirty[i][j] = true;
        }
    }
    UpdateTextureAll();

}

MiniMap::~MiniMap() {

}

void MiniMap::DrawMinimap() {

    UpdateTextureAll();
    SDL_RenderCopy(Game::Renderer, MiniMapTexture, NULL, &dstRect);
}

void MiniMap::UpdateMinimap(int arr[NUMBER_OF_SQUARE][NUMBER_OF_SQUARE]) {
    for (int i = 0; i < NUMBER_OF_SQUARE; i++) {
        for (int j = 0; j < NUMBER_OF_SQUARE; j++) {
            miniMap[i][j] = arr[i][j];
        }
    }
    UpdateTextureAll();
}

void MiniMap::UpdateMinimap(int x, int y, int tile) {
    if (miniMap[x][y] != tile)
    {
        miniMap[x][y] = tile;
        miniMapDirty[x][y] = true;
    }
}

void MiniMap::UpdateTextureAll() {
    SDL_SetRenderTarget(Game::Renderer, MiniMapTexture);
    //SDL_RenderClear(Game::Renderer);

    bool temp = false;

    for (int x = 0; x < NUMBER_OF_SQUARE; x++) {
        for (int y = 0; y < NUMBER_OF_SQUARE; y++) {
            if(miniMapDirty[x][y])
            {
                temp = true;
                SDL_Color color = ColorArray[miniMap[x][y]];
                squareRect.x = EDGE_PADDING + x * (squareRect.w + MINIMAP_PADDING);
                squareRect.y = EDGE_PADDING + y * (squareRect.h + MINIMAP_PADDING);

                SDL_SetRenderDrawColor(Game::Renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(Game::Renderer, &squareRect);
                miniMapDirty[x][y] = false;
            }
        }
    }

    SDL_SetRenderDrawColor(Game::Renderer, 255, 255, 255, 255);
    SDL_SetRenderTarget(Game::Renderer, NULL);
}

void MiniMap::UpdateTextureOne(int x, int y) {
    SDL_SetRenderTarget(Game::Renderer, MiniMapTexture);


    SDL_Color Color = ColorArray[miniMap[x][y]];
    squareRect.x = EDGE_PADDING + x * (squareRect.w + MINIMAP_PADDING);
    squareRect.y = EDGE_PADDING + y * (squareRect.h + MINIMAP_PADDING);

    std::cout << "squareRect   X = " << squareRect.x << " Y = " << squareRect.y << std::endl;

    SDL_SetRenderDrawColor(Game::Renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderFillRect(Game::Renderer, &squareRect);


    SDL_SetRenderDrawColor(Game::Renderer, 255, 255, 255, 255);
    SDL_SetRenderTarget(Game::Renderer, NULL);
}
