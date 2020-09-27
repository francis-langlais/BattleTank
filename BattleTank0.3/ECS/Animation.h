//
// Created by eee466 on 13/05/19.
//
#pragma once

struct Animation
{

    int index;
    int frames;
    int speed;

    Animation() {}
    Animation(int i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
    }

};