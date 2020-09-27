#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "ECS/ECS.h"
#include "Vector2D.h"
#include <vector>

/* For minimap sake:
 * If you want 2 pixel/square, 1 in-between and 2 edge spacing : 1278 x 900
 * If you want 3 pixel/square, 0 in-between and 2 edge spacing : 1279 x 900
*/

#define SCREEN_WIDTH    1279
#define SCREEN_HEIGHT   900

//Maps are always squared.
//#define MAP_SIZE                8000
#define TILE_SIZE               64
#define NUM_TILE                (1024)

class AssetManager;
class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);

    void HandleEvent();
    void Render();
    void Update();

    static void CreateEntity(int posX, int posY, int rot, std::string tex);
    static void UpdateEntity(int id, int posX, int posY, int rot, int hp);
    static void DestroyEntity(int id);
    static void UpdateText(std::string text);
    static void UpdateMinimap(int x, int y, int col);

    bool running();
    void Clean();

    static SDL_Renderer* Renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager* assets;
    static int entityID;
    static Vector2D<float> GlobalCamera;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupColliders,
        groupProjectiles
    };


private:
    SDL_Window* Window;
};
