#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double rot, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::Renderer, tex, &src, &dst, rot, NULL, flip);
}