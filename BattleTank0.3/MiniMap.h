//
// Created by eee466 on 25/06/19.
//

#pragma once


#include <SDL_system.h>

// Look at Game.h for resolution depending on minimap setting.
#define EDGE_PADDING        2
#define MINIMAP_PADDING     0
#define NUMBER_OF_SQUARE    125

class MiniMap {
public:
    MiniMap();
    ~MiniMap();

    void DrawMinimap();
    void UpdateMinimap(int arr[NUMBER_OF_SQUARE][NUMBER_OF_SQUARE]);
    void UpdateMinimap(int x, int y, int tile);

private:
    SDL_Texture* MiniMapTexture;

    int miniMap[NUMBER_OF_SQUARE][NUMBER_OF_SQUARE];
    bool miniMapDirty[NUMBER_OF_SQUARE][NUMBER_OF_SQUARE];

    void UpdateTextureAll();
    void UpdateTextureOne(int x, int y);

    SDL_Rect dstRect;
    SDL_Rect squareRect;

    SDL_Color ColorArray[9] = {
            {0, 0, 0, 255},         // 0 - Black
            {255, 0, 0, 255},       // 1 - Red
            {0, 255, 0, 255},       // 2 - Green
            {0, 0, 255, 255},       // 3 - Blue
            {220, 220, 220, 255},   // 4 - Gray
            {245, 164, 66, 255},    // 5 - Orange
            {245, 245, 66, 255},    // 6 - Yellow
            {150, 66, 245, 255},    // 7 - Purple
            {245, 66, 245, 255}     // 8 - Pink
    };

    int rightspace;

};
