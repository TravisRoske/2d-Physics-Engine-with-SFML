#pragma once

#include <math.h>

class Velocity
{
public:
    float speed;
    int direction;

    Velocity()
    {
        speed = 0.f;
        direction = 0;
    }

    Velocity(float speed, int direction)
    {
        this->speed = speed;
        this->direction = direction;
    }


    sf::Vector2f getMovement()//Gets the amount of movement to the object this vector would calculate to, in pixels
    {
        sf::Vector2f move;
        move.x = cos(direction) * speed;
        move.y = sin(direction) * speed;

        return move;
    }




    Velocity &operator+(const Velocity &v2)     //Overloaded operator for adding two velocities together
    {
        Velocity result;

        float x = (cos(this->direction) * this->speed) + (cos(v2.direction) * v2.speed);    //Adds the x offset of the two vectors, calculates over 1 frame of time
        float y = (sin(this->direction) * this->speed) + (sin(v2.direction) * v2.speed);    //Adds the y offset of the two vectors


        result.speed = sqrt(pow(2, x) + pow(2, y));
        result.direction = asin(static_cast<double>(y/result.speed));   //uses arcsine of y over speed to get the new angle

        return result;
    }

//Vector math...

//How to convert speed and direction into movement


//speed, pixels per frame... so 1 is 60 pixels a second.
//direction, in degrees, starting with 0 at the right, moving counterclockwise around to 360(needs to be int for modulo to work on it)
//
//y = sin(direction) * speed;
//x = cos(direction) * speed;


//Adding two velocities together...
//



private:


};
