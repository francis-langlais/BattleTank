//
// Created by eee466 on 04/03/19.
//

#ifndef BATTLETANK0_1_SPRITESHEETANIM_H
#define BATTLETANK0_1_SPRITESHEETANIM_H


#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class spriteSheetAnim {

public:
    spriteSheetAnim(SDL_Renderer* gRenderer, std::string path, SDL_Point FrameNbr, SDL_Point Position);
    void update();

private:
    SDL_Rect GetNextFrame();
    SDL_Texture* loadTexture(SDL_Renderer* gRenderer, std::string path);
    ~spriteSheetAnim();

private:
    SDL_Texture* SpriteSheet = nullptr;
    SDL_Point Coordinate;
    SDL_Renderer* gRenderer;

    SDL_Point NbrFrame;
    SDL_Point ImgPixelCount;
    SDL_Point TextureSize;

    SDL_Rect CurrentFrameRect;

    int TotalFrameCount;
    int CurrentFrame;

public:
    bool isDone = false;
    SDL_Texture* CurrentSprite = nullptr;
    SDL_Rect SpritePos;
    SDL_Rect ImgRec;

};


#endif //BATTLETANK0_1_SPRITESHEETANIM_H
