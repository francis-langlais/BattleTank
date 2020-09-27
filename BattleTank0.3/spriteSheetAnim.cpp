//
// Created by eee466 on 04/03/19.
//

#include "spriteSheetAnim.h"

spriteSheetAnim::spriteSheetAnim(SDL_Renderer* gRenderer, std::string path, SDL_Point FrameNbr, SDL_Point Position) {

    SpriteSheet = loadTexture(gRenderer, "./Ressources/Image/Explosion.png");

    SDL_QueryTexture(SpriteSheet, NULL, NULL, &TextureSize.x, &TextureSize.y);

    NbrFrame = FrameNbr;
    this->gRenderer = gRenderer;

    ImgPixelCount.x = TextureSize.x / NbrFrame.x;
    ImgPixelCount.y = TextureSize.y / NbrFrame.y;
    Coordinate.x = Position.x - (ImgPixelCount.x / 2);
    Coordinate.y = Position.y - (ImgPixelCount.y / 2);
    SpritePos = {Coordinate.x, Coordinate.y, ImgPixelCount.x, ImgPixelCount.y};
    ImgRec = {0, 0, ImgPixelCount.x, ImgPixelCount.y};

    TotalFrameCount = NbrFrame.x * NbrFrame.y;
    CurrentFrame = 0;

    CurrentSprite = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ImgPixelCount.x, ImgPixelCount.y);
    SDL_SetTextureBlendMode(CurrentSprite, SDL_BLENDMODE_BLEND);

}

SDL_Texture* spriteSheetAnim::loadTexture(SDL_Renderer* gRenderer, std::string path) {

    SDL_Texture* temp;
    //Loading a tank image and check if the image is loaded properly
    temp = IMG_LoadTexture(gRenderer, path.c_str());
    if (temp == nullptr) {
        std::cout << "spriteSheetAnim::loadTexture -> IMG_Load: " << IMG_GetError() << "\n";
        return nullptr;
    }

    return temp;
}

spriteSheetAnim::~spriteSheetAnim() {

    SDL_DestroyTexture(SpriteSheet);
    free(this);
}

SDL_Rect spriteSheetAnim::GetNextFrame() {

    if (isDone) {
        std::cout << "Animation is done. THIS SHOULD NEVER HAPPEN" << std::endl;
    }

    int x = (CurrentFrame % NbrFrame.x) * ImgPixelCount.x;
    int y = (CurrentFrame / NbrFrame.y) * ImgPixelCount.y;

    CurrentFrame++;

    if (CurrentFrame >= TotalFrameCount) {
        isDone = true;
    }

    return {x, y, ImgPixelCount.x, ImgPixelCount.y};
}

void spriteSheetAnim::update() {

    CurrentFrameRect = GetNextFrame();

    SDL_SetRenderTarget(gRenderer, CurrentSprite);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, SpriteSheet, &CurrentFrameRect, &ImgRec);

    SDL_SetRenderTarget(gRenderer, NULL);
}
