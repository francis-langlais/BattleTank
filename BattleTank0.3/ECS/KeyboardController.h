//
// Created by eee466 on 13/05/19.
//

#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                    break;
                case SDLK_w:
                    transform->velocity.y = -1;

                    transform->velTest = 1;

                    if (sprite->isAnimated())
                        sprite->Play("Walk");
                    break;
                case SDLK_a:
                    transform->RotSpeed = -1;
                    if (sprite->isAnimated())
                        sprite->Play("Walk");
                    break;
                case SDLK_d:
                    transform->RotSpeed = 1;
                    if (sprite->isAnimated())
                        sprite->Play("Walk");
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;

                    transform->velTest = -1;

                    if (sprite->isAnimated())
                        sprite->Play("Walk");
                    break;
                default:
                    break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
                case SDLK_w:
                    transform->velocity.y = 0;

                    transform->velTest = 0;

                    if (sprite->isAnimated())
                        sprite->Play("Idle");
                    break;
                case SDLK_a:
                    transform->RotSpeed = 0;
                    if (sprite->isAnimated())
                        sprite->Play("Idle");
                    break;
                case SDLK_d:
                    transform->RotSpeed = 0;
                    if (sprite->isAnimated())
                        sprite->Play("Idle");
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;

                    transform->velTest = 0;

                    if (sprite->isAnimated())
                        sprite->Play("Idle");
                    break;
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                default:
                    break;
            }
        }
    }
};