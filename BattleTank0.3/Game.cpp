#include "Game.h"
#include "Map.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "CollisionDetection.h"
#include "MiniMap.h"
#include "UI/TextBox.h"
#include "UI/ProgressBar.h"
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>

AssetManager* Game::assets = new AssetManager(&manager);
Manager manager;

Map* map;
MiniMap* minimap;
TextBox* textBox;
ProgressBar* progressBar;

SDL_Renderer* Game::Renderer = nullptr;
SDL_Event Game::event;
//std::vector<ColliderComponent*> Game::colliders;

SDL_Rect Game::camera = { 0,0,SCREEN_HEIGHT,SCREEN_HEIGHT };

bool Game::isRunning = false;
int Game::entityID = 2;
Vector2D<float> Game::GlobalCamera = {0, 0};

//EntityID 0 = Network - DO NOT TRY TO USE ID 0 OR YOU WILL LOSE YOUR GUI.
Entity& Network(manager.addEntity());
Entity& Player(manager.addEntity());
Entity& Obst(manager.addEntity());

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char* title, int posX, int posY, int width, int height, bool fullscreen)
{
    int flags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << std::endl << "SDL initialized..." << std::endl;

        Window = SDL_CreateWindow(title, posX, posY, width, height, flags);
        if (Window)
        {
            std::cout << "Window initialized..." << std::endl;
        }

        Renderer = SDL_CreateRenderer(Window, -1, 0);
        if (Renderer)
        {
            SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
            std::cout << "Renderer initialized..." << std::endl;
        }

        if (TTF_Init() == 0) {
            std::cout << "TTF initialized..." << std::endl;

        }
    }

    //Adding texture to the asset manager.
    assets->AddTexture("player", "Ressources/Image/Tanks/tank.png");
    assets->AddTexture("enemy", "Ressources/Image/Tanks/tank_red.png");
    assets->AddTexture("player_shield", "Ressources/Image/player_shield.png");
    assets->AddTexture("enemy_shield", "Ressources/Image/enemy_shield.png");

    assets->AddFont("courier15", "Font/COURIER.ttf", 1);
    assets->AddFont("space", "Font/SpaceMono-Regular.ttf", 15);

    //Creating Network capability.
    Network.addComponent<NetworkController>();

    //Adding all the component to the Player Entity.
    Player.addComponent<TransformComponent>(100.0f, 100.0f, 64, 64, 1);
    Player.addComponent<SpriteComponent>(256, 256, "player", false);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player", CIRCLE, Player.getComponent<TransformComponent>().width);
    Player.addGroup(groupPlayers);

    Obst.addComponent<TransformComponent>(200.0f, 200.0f, 64, 64, 1);
    Obst.addComponent<SpriteComponent>(256, 256, "enemy_shield", false);
    Obst.addGroup(groupPlayers);

    //Creating the Map.
    map = new Map();
    minimap = new MiniMap();
    textBox = new TextBox();
    progressBar = new ProgressBar(10, 10, 500, 20);

    std::cout << "We're ready to roll!" << std::endl;

    isRunning = true;
}

auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::HandleEvent()
{

    while(SDL_PollEvent(&event)) {

        //Player needs a PlayerMovementComponent or else the game will crash.
        //Right now the player is controlled with the keyboard but later on it
        //can be control with some logic.
        Player.getComponent<KeyboardController>().update();

        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::Render()
{
   SDL_RenderClear(Renderer);

   map->DrawMap(camera.x, camera.y);
   minimap->DrawMinimap();
   textBox->DrawTextbox();
   progressBar->draw();

   for (auto& c : colliders)
   {
       c->draw();
   }

   for(auto& p : players)
   {
       p->draw();
   }

   SDL_RenderPresent(Renderer);
}

void Game::Update()
{

    manager.refresh();
    manager.update();
    //colliders = manager.getGroup(Game::groupColliders);

    for(auto& c : colliders)
    {
        if(CollisionDetection::CC(Player.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>()))
        {
            std::cout << "Collision detected!" << std::endl;
        }
    }

    camera.x = static_cast<int>(Player.getComponent<TransformComponent>().position.x - SCREEN_HEIGHT / 2 + (Player.getComponent<TransformComponent>().width / 2));
    camera.y = static_cast<int>(Player.getComponent<TransformComponent>().position.y - SCREEN_HEIGHT / 2 + (Player.getComponent<TransformComponent>().height / 2));

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > EngineMath::TileToPixel(NUM_TILE) - SCREEN_HEIGHT)
        camera.x = EngineMath::TileToPixel(NUM_TILE) - SCREEN_HEIGHT;
    if (camera.y > EngineMath::TileToPixel(NUM_TILE) - SCREEN_HEIGHT)
        camera.y = EngineMath::TileToPixel(NUM_TILE) - SCREEN_HEIGHT;
}

bool Game::running() {
    if(!isRunning)
        Network.getComponent<NetworkController>().networkRunning = false;
    return isRunning;

}

void Game::Clean()
{
    free(map);
    free(minimap);
    free(textBox);
    free(progressBar);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    assets->~AssetManager();
    SDL_Quit();

    std::cout << "SDL has bean cleaned up!" << std::endl;

}

void Game::CreateEntity(int posX, int posY, int rot, std::string tex) {

    manager.addEntity();
    manager.GetEntityAt(entityID)->addComponent<TransformComponent>(posX, posY, 64, 64, 1);
    manager.GetEntityAt(entityID)->getComponent<TransformComponent>().rotation = rot;
    manager.GetEntityAt(entityID)->addComponent<SpriteComponent>(256, 256, tex, false);
    manager.GetEntityAt(entityID)->addComponent<ColliderComponent>(tex, CIRCLE, 64);
    entityID++;

}

void Game::UpdateEntity(int id, int posX, int posY, int rot, int hp) {

    manager.GetEntityAt(id)->getComponent<TransformComponent>().position.x = posX;
    manager.GetEntityAt(id)->getComponent<TransformComponent>().position.y = posY;
    manager.GetEntityAt(id)->getComponent<TransformComponent>().rotation = rot;

    if(id == 1)
        progressBar->update(hp);
}

void Game::DestroyEntity(int id) {
    if(id != 0)
        manager.GetEntityAt(id)->destroy();
    else
        std::cout << "You are trying to remove to ability to use this interface. Please use an ID other than 0" << std::endl;
}

void Game::UpdateText(std::string text) {
    textBox->AddString(text);
}

void Game::UpdateMinimap(int x, int y, int col) {
    minimap->UpdateMinimap(x, y, col);
}
