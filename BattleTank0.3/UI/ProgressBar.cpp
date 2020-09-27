//
// Created by eee466 on 03/07/19.
//

#include "ProgressBar.h"
#include "../Game.h"

ProgressBar::ProgressBar(int x, int y, int w, int h)
{
    dstRect = {x, y, w, h};
    srcRect = {x, y, w, h};

    BackgroundText = SDL_CreateTexture(Game::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    ProgressBarText = SDL_CreateTexture(Game::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    SDL_SetRenderTarget(Game::Renderer, BackgroundText);
    SDL_SetRenderDrawColor(Game::Renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::Renderer);

    SDL_SetRenderTarget(Game::Renderer, ProgressBarText);
    SDL_SetRenderDrawColor(Game::Renderer, 0, 255, 0, 255);
    SDL_RenderClear(Game::Renderer);

    SDL_SetRenderDrawColor(Game::Renderer, 255, 255, 255, 255);
    SDL_SetRenderTarget(Game::Renderer, NULL);
}

ProgressBar::~ProgressBar() {
    SDL_DestroyTexture(BackgroundText);
    SDL_DestroyTexture(ProgressBarText);
}

void ProgressBar::update(int value) {
    float hp = static_cast<float>(value);
    srcRect.w = static_cast<int>(dstRect.w * (hp / MAX_VALUE));

}

void ProgressBar::draw() {
    SDL_RenderCopy(Game::Renderer, BackgroundText, NULL, &dstRect);
    SDL_RenderCopy(Game::Renderer, ProgressBarText, NULL, &srcRect);
}
