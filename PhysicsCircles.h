#pragma once

#include <SFML/Graphics.hpp>
#include "math.h"
//#include <Vector2.hpp>


//My custom circles.
//extends circleshapes but also has velocity

class PhysicsCircles : public sf::CircleShape
{
public:
    MyVelocity velocity;
    float weight;
    bool physicsOn = true;
    bool deleteThis = false;

    PhysicsCircles(float radius, float speed, float direction)
    {
        this->setRadius(radius);
        this->velocity.speed = speed;
        this->velocity.direction = direction;
        this->weight = (3.1415 * pow(radius, 2)); //calculates weight by area of circle
    }

    PhysicsCircles(float radius, float speed, float direction, float weight)
    {
        this->setRadius(radius);
        this->velocity.speed = speed;
        this->velocity.direction = direction;
        this->weight = weight;
    }

    void update()
    {
        if(physicsOn)
            this->move(velocity.getMovement());
        else
            velocity.zero();
    }

};
