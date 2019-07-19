#pragma once

#include <math.h>
#include "Collisions.h"


class MyVelocity
{
public:
    float speed;
    float direction;

    MyVelocity()
    {
        speed = 0.f;
        direction = 0.f;
    }


    MyVelocity(float speed, float direction)
    {
        this->speed = speed;
        recalcAngle(direction);
        this->direction = direction;
    }

    void zero()
    {
        speed = 0.f;
        direction = 0.f;
    }

    sf::Vector2f getMovement()//Gets the amount of movement to the object this vector would calculate to, in pixels
    {
        sf::Vector2f move;
        move.x = cosDegrees(direction) * speed;
        move.y = sinDegrees(direction) * speed;

        return move;
    }


    static float getVelocityAngle(sf::Vector2f move) //Gets angle from a movement Vector
    {
        float angle;
        angle = aTanDegrees(move.y, move.x);   //uses arctan of y over x to get the new angle
        angle = recalcAngle(angle);

        return angle;
    }


    MyVelocity &operator+=(MyVelocity &vrhs)     //Overloaded operator for adding two velocities together
    {
        //float x = (cosDegrees(this->direction) * this->speed) + (cosDegrees(vrhs.direction) * vrhs.speed);    //Adds the x offset of the two vectors, calculates over 1 frame of time
        //float y = (sinDegrees(this->direction) * this->speed) + (sinDegrees(vrhs.direction) * vrhs.speed);    //Adds the y offset of the two vectors

        sf::Vector2f mv1 = this->getMovement();
        sf::Vector2f mv2 = vrhs.getMovement();

        mv1 += mv2;

        this->speed = sqrt(pow(mv1.x, 2) + pow(mv1.y, 2));
        this->direction = getVelocityAngle(mv1);

        return *this;
    }


    //===========To Convert radians to degrees and back for sin and cos==========
    static constexpr float pi = 3.14159265358979323846;

    static inline float sinDegrees (float x) { return sin(x * pi / 180.0); }//covert degree to radians for sin
    static inline float cosDegrees (float x) { return cos(x * pi / 180.0); }//covert degree to radians for cos

    static inline float aTanDegrees (float x, float y) { return (atan2(x, y) * 180.0 / pi); }
    //============================================================================


//Vector math...

//How to convert speed and direction into movement


//speed, pixels per frame... so 1 is 60 pixels a second.
//direction, in degrees, starting with 0 at the right, moving counterclockwise around to 360(needs to be int for modulo to work on it)
//
//y = sin(direction) * speed;
//x = cos(direction) * speed;


//Adding two velocities together...
//


};
