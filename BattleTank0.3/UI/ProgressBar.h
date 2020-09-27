//
// Created by eee466 on 03/07/19.
//

#pragma once

#include <SDL_system.h>

#define MAX_VALUE 100

class ProgressBar {

private:
    SDL_Texture* BackgroundText;
    SDL_Texture* ProgressBarText;

    SDL_Rect dstRect;
    SDL_Rect srcRect;

public:


    ProgressBar(int x, int y, int w, int h);

    void update(int value);

    void draw();

    virtual ~ProgressBar();
};
