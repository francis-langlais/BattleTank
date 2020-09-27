//
// Created by eee466 on 02/07/19.
//

#include "TextBox.h"
#include <sstream>
#include "../Game.h"
#include "../AssetManager.h"

TextBox::TextBox()
{
    srcRect = {0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT - (SCREEN_WIDTH - SCREEN_HEIGHT)};
    dstRect = {SCREEN_WIDTH - (SCREEN_WIDTH - SCREEN_HEIGHT), 0, srcRect.w, srcRect.h};
    textDstRect = {dstRect.x + PADDING, dstRect.y + PADDING, dstRect.w - PADDING, dstRect.h - PADDING};
    textSrcRect = {0, 0, 0, 0};
    BoxTexture = SDL_CreateTexture(Game::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, srcRect.w, srcRect.h);
    TextColor.r = 255;
    TextColor.g = 255;
    TextColor.b = 255;
    TextColor.a = 255;

    SDL_SetRenderTarget(Game::Renderer, BoxTexture);
    SDL_SetRenderDrawBlendMode(Game::Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(BoxTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::Renderer, 159, 159, 159, 255);
    SDL_RenderClear(Game::Renderer);
    SDL_SetRenderDrawColor(Game::Renderer, 255, 255, 255, 255);
    SDL_SetRenderTarget(Game::Renderer, NULL);

    AddString("Test nmew line that wraps and new line");
    AddString("Empty Textbox");
}

TextBox::~TextBox() {
    SDL_DestroyTexture(BoxTexture);
    SDL_DestroyTexture(TextTexture);
}

void TextBox::DrawTextbox() {


    SDL_RenderCopy(Game::Renderer, BoxTexture, NULL, &dstRect);
    SDL_RenderCopy(Game::Renderer, TextTexture, &textSrcRect, &textDstRect);
}

void TextBox::UpdateTextTexture(){

    std::ostringstream SStream;

    for(std::string s : StringVec)
    {
        SStream << s << std::endl;
    }

    SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(Game::assets->GetFont("space"), SStream.str().c_str(), TextColor, srcRect.w - PADDING);
    TextTexture = SDL_CreateTextureFromSurface(Game::Renderer, surf);
    SDL_FreeSurface(surf);

    SDL_QueryTexture(TextTexture, nullptr, nullptr, &textSrcRect.w, &textSrcRect.h);


    if (textSrcRect.h > dstRect.h)
    {
        if(textSrcRect.h > dstRect.h * 2)
        {
            std::cout << "Removing first string: " << StringVec[0] << std::endl;
            StringVec.erase(StringVec.begin());
        }
        textSrcRect.y = textSrcRect.h - dstRect.h;
        textSrcRect.h = dstRect.h;
    }

    textDstRect.w = textSrcRect.w;
    textDstRect.h = textSrcRect.h;

}

void TextBox::AddString(std::string text) {
    StringVec.push_back(text);
    UpdateTextTexture();
}
