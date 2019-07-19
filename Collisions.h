#pragma once

#include "math.h"

float recalcAngle(float angle)
{
    while(angle < 0)
    {
        angle += 360;
    }
    while(angle >= 360)
    {
        angle -= 360;
    }

    return angle;
}

float reflectAngle(float ang)
{
    float temp = 90 - ang;

    ang = ang + (2 * temp);
    ang = recalcAngle(ang);

    return ang;
}

float reverseAngle(float ang)
{
    ang = (ang + 180);

    return recalcAngle(ang);
}

float getCollisionAngle (float direction, float normal)
{
    float result;
    if(normal - 90 <= direction && normal + 90 >= direction)
        result = direction;//do nothing
    else
    {
        result = recalcAngle((reverseAngle(direction) + 2 * (normal - reverseAngle(direction))));
    }

    return result;
}

float getDistance(const sf::Vector2f &first, const sf::Vector2f & second)
{
    return(sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2)));
}



