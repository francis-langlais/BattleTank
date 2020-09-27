//
// Created by eee466 on 08/05/19.
//

#pragma once

#include "Vector2D.h"

class EngineMath
{
public:
    static double SquaredDistance (Vector2D<float> vec1, Vector2D<float> vec2)
    {
        float deltaX = vec2.x - vec1.x;
        float deltaY = vec2.y - vec1.y;

        return deltaX * deltaX + deltaY * deltaY;
    }

    static double DegreeToRad(int deg)
    {
        return deg * 3.14159265 / 180.0;
    }

    static int TileToPixel (float tile)
    {
        return static_cast<int>(tile * 64);
    }

    static float PixelToTile (int pixel)
    {
        return static_cast<float>(pixel / 64.0f);
    }
};
