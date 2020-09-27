#include "Game.h"
#include <iostream>

#define TARGET_FPS	    30


Game* MyGame = nullptr;
int missFrame = 0;

int main(int argc, char *argv[])
{
    MyGame = new Game();

    Uint32 MaxFrameTime = 1000 / TARGET_FPS;

    Uint32 FrameStart = 0;
    Uint32 FrameTime;

    MyGame->init("BattleTank", 100, 50, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    Uint32 TimeStart = SDL_GetTicks();

    std::cout << std::endl << "Game is running..." << std::endl << std::endl;
    while (MyGame->running())
    {
        FrameStart = SDL_GetTicks();

        MyGame->HandleEvent();
        MyGame->Update();
        MyGame->Render();

        FrameTime = SDL_GetTicks() - FrameStart;

        if (MaxFrameTime > FrameTime)
        {
            SDL_Delay(MaxFrameTime - FrameTime);
        } else {
            missFrame++;
        }
    }

    std::cout << std::endl;
    std::cout << "Game is running at " << TARGET_FPS << " FPS" << std::endl;
    std::cout << "Total running time: " << (float)((SDL_GetTicks() - TimeStart) / 1000.0f) << " seconds" << std::endl;
    std::cout << "Total number of miss frame: " << missFrame << std::endl;
    MyGame->Clean();
    free(MyGame);

    return 0;
}
