//
// Created by eee466 on 02/07/19.
//

#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include <SDL_ttf.h>

#define PADDING 5

class TextBox {

private:
    SDL_Texture* BoxTexture;
    SDL_Texture* TextTexture;

    SDL_Rect textDstRect;
    SDL_Rect textSrcRect;
    SDL_Rect dstRect;
    SDL_Rect srcRect;

    std::vector<std::string> StringVec;

    SDL_Color TextColor;

public:
    std::string strings;

    TextBox();
    virtual ~TextBox();

    void DrawTextbox();
    void UpdateTextTexture();
    void AddString(std::string text);
};
