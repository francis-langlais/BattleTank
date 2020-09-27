//
// Created by eee466 on 09/05/19.
//

#include "CollisionDetection.h"
#include "ECS/ColliderComponent.h"

bool CollisionDetection::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB)
{
    if (
            rectA.x + rectA.w >= rectB.x &&
            rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y &&
            rectB.y + rectB.h >= rectA.y
            )
    {
        return true;
    }

    return false;
}

bool CollisionDetection::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if (colA.mCollider->type != BOX || colB.mCollider->type != BOX)
    {
        std::cout << "CollisionDetection Error: Collider are not of type BOX" << std::endl;
        return false;
    }

    BoxCollider* boxA = static_cast<BoxCollider*>(colA.mCollider);
    BoxCollider* boxB = static_cast<BoxCollider*>(colB.mCollider);

    if (!(boxA && boxB))
    {
        std::cout << "CollisionDetection Error: static_cast failed" << std::endl;
        return false;
    }

    if(AABB(boxA->collider, boxB->collider))
    {
        //std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    } else {
        //std::cout << colA.tag << " hit nothing" << std::endl;
    }

    return false;
}

/*           OBB DETECTION
 *  1- Calculez les points rotated
 *      a- Calculer vector poitant vers le coins (point - centre)
 *      b- Rotate vecteur en utilisant la matrice de rotation | cos(a)    -sin(a) | |x| = | x * cos(a) - y * sin(a) | = |x'|
 *                                                            | sin(a)     cos(a) | |y|   | x * sin(a) + y * cos(a) |   |y'|
 *      c- Calculez la position du point rotated (centre + vecteur rotated)
 *  2- Calculez les normales
 *      a- N1 -> Vec1 = (P1 - P2)  N1 = (Vec1.y, -Vec1.x)
 *      b- N2 -> Vec2 = (P2 - P3)  N2 = (vec2.y, -Vec2.x)
 *  3- Faire le DOT product des points des 2 shapes sur tout les normales et si une normale
 *      retourne un non-overlap, il n'y a pas collision. (voir le tread reddit pour plus de detail https://www.reddit.com/r/gamedev/comments/brb88i/question_bout_obb_collision_detection/)
 *  4- Pour chaque normal, evaluer si le min/max des dot product et voir s'il y a une collision.
 *
*/

//TODO This work ish. Need further testing with filled SDL_Rect to physically see.

bool CollisionDetection::OBB(const ColliderComponent &colA, const ColliderComponent &colB) {

    //Getting the right kind of collider.
    const BoxCollider* boxA = static_cast<BoxCollider*>(colA.mCollider);
    const BoxCollider* boxB = static_cast<BoxCollider*>(colB.mCollider);

    if (!(boxA && boxB))
    {
        std::cout << "CollisionDetection Error: static_cast failed" << std::endl;
        return false;
    }

    const SDL_Rect rectA = boxA->collider;
    const SDL_Rect rectB = boxB->collider;

    /***************** 1 *****************/
    //Point are designated like this: top-left, top-right, bottom-right, bottom-left.
    Vector2D<int> pointA[4];
    pointA[0] = {rectA.x, rectA.y};
    pointA[1] = {rectA.x + rectA.w,rectA.y};
    pointA[2] = {rectA.x + rectA.w,rectA.y + rectA.h};
    pointA[3] = {rectA.x, rectA.y + rectA.h};

    //std::cout << "Angle = " << colA.entity->getComponent<TransformComponent>().rotation << std::endl << " Point0 = " << pointA[0] << std::endl << " Point1 = " << pointA[1] << std::endl << " Point2 = " << pointA[2] << std::endl << " Point3 = " << pointA[3] << std::endl;

    Vector2D<int> pointB[4];
    pointB[0] = {rectB.x, rectB.y};
    pointB[1] = {rectB.x + rectB.w,rectB.y};
    pointB[2] = {rectB.x + rectB.w,rectB.y + rectB.h};
    pointB[3] = {rectB.x, rectB.y + rectB.h};

    Vector2D<int> centerA = {rectA.x + rectA.w / 2, rectA.y + rectA.h / 2};
    Vector2D<int> centerB = {rectB.x + rectB.w / 2, rectB.y + rectB.h / 2};

    std::cout << "Centre = " << centerA << std::endl;

    //Getting a Vector starting from the center and pointing to each point.
    Vector2D<int> rotVecA[4];

    Vector2D<int> rotVecB[4];


    //Rotate each vector using this rotation matrix | cos(a)    -sin(a) | |x| = | x * cos(a) - y * sin(a) | = |x'|
    //                                              | sin(a)     cos(a) | |y|   | x * sin(a) + y * cos(a) |   |y'|
    if (colA.entity->getComponent<TransformComponent>().rotation != 0)
    {

        float sinA = sin(EngineMath::DegreeToRad(colA.entity->getComponent<TransformComponent>().rotation));
        float cosA = cos(EngineMath::DegreeToRad(colA.entity->getComponent<TransformComponent>().rotation));
        for (int i = 0; i < 4; i++) {
            rotVecA[i] = pointA[i] - centerA;
            int tempx = rotVecA[i].x * cosA - rotVecA[i].y * sinA;
            int tempy = rotVecA[i].x * sinA + rotVecA[i].y * cosA;
            rotVecA[i] = {tempx, tempy};
            pointA[i] = rotVecA[i] + centerA;
        }

    }


    if (colB.entity->getComponent<TransformComponent>().rotation != 0)
    {
        float sinB = sin(EngineMath::DegreeToRad(colB.entity->getComponent<TransformComponent>().rotation));
        float cosB = cos(EngineMath::DegreeToRad(colB.entity->getComponent<TransformComponent>().rotation));
        for (int i = 0; i < 4; i++) {
            rotVecB[i] = pointB[i] - centerB;
            rotVecB[i] = {static_cast<int>(rotVecB[i].x * cosB - rotVecB[i].y * sinB), static_cast<int>(rotVecB[i].x * sinB + rotVecB[i].y * cosB)};
            pointB[i] = rotVecB[i] + centerB;
        }
    }
    //Calculate the point of the rotated box

    /***************** 2 *****************/
    //This currently only works for box. Need adjustment to work with any polygon.

    Vector2D<int> normals[4];
    Vector2D<int> temp;

    /*
    temp = pointA[0] - pointA[1];
    normals[0] = {temp.y, -temp.x};
    temp = pointA[1] - pointA[2];
    normals[1] = {temp.y, -temp.x};
    temp = pointB[0] - pointB[1];
    normals[2] = {temp.y, -temp.x};
    temp = pointB[1] - pointB[2];
    normals[3] = {temp.y, -temp.x};
    */


    temp = pointA[0] - pointA[1];
    temp = centerA + temp;
    temp = {temp.y, -temp.x};
    normals[0] = temp;

    temp = pointA[1] - pointA[2];
    temp = centerA + temp;
    temp = {temp.y, -temp.x};
    normals[1] = temp;

    temp = pointB[0] - pointB[1];
    temp = centerB + temp;
    temp = {temp.y, -temp.x};
    normals[2] = temp;

    temp = pointB[1] - pointB[2];
    temp = centerB + temp;
    temp = {temp.y, -temp.x};
    normals[3] = temp;

    /***************** 3 *****************/

    // X = normal Y = minA, maxA, minB, maxB

    float dotResult[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dotResult[i][j] = 0.0f;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float tempA = DotProduct(normals[i], pointA[j]);
            float tempB = DotProduct(normals[i], pointB[j]);

            //Setting min and max equals to the first value.
            if(j == 0)
            {
                dotResult[i][0] = tempA;
                dotResult[i][1] = tempA;
                dotResult[i][2] = tempB;
                dotResult[i][3] = tempB;
            } else
            {
                //Adjusting min/max.
                if(tempA < dotResult[i][0])
                    dotResult[i][0] = tempA;
                if(tempA > dotResult[i][1])
                    dotResult[i][1] = tempA;
                if(tempB < dotResult[i][2])
                    dotResult[i][2] = tempB;
                if(tempB > dotResult[i][3])
                    dotResult[i][3] = tempB;
            }
        }
    }

    /***************** 4 *****************/

    for (int i = 0; i < 4; i++) {
        if(dotResult[i][1] < dotResult[i][2] ||
            dotResult[i][3] < dotResult[i][0])
        {
            return false;
        }
    }

    return true;
}

bool CollisionDetection::CC(const ColliderComponent &colA, const ColliderComponent &colB) {

    //Getting the right kind of collider.
    const CircleCollider* circleA = static_cast<CircleCollider*>(colA.mCollider);
    const CircleCollider* circleB = static_cast<CircleCollider*>(colB.mCollider);

    if (!(circleA && circleB))
    {
        std::cout << "CollisionDetection Error: static_cast failed" << std::endl;
        return false;
    }

    Vector2D<int> posA = circleA->position;
    Vector2D<int> posB = circleB->position;

    return (posA.x - posB.x) * (posA.x - posB.x) +
            (posA.y - posB.y) * (posA.y - posB.y) <=
            (circleA->radius + circleB->radius) * (circleA->radius + circleB->radius);
}
