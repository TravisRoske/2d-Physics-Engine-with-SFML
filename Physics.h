#pragma once

#include "MyVelocity.h"
#include "PhysicsCircles.h"
#include "BoundingBox.h"
#include "Values.h"
#include "Collisions.h"


BoundingBox boundingBox(windowH, 0, windowW);

class Physics
{
public:
    MyVelocity grav;

    Physics() :grav(gravity, 90.f){}//Gravity constant going down

    void runGravity(std::vector<PhysicsCircles*> &circles)
    {
        for(size_t i = 0;  i < circles.size(); i++)
        {
            circles.at(i)->velocity += grav;
        }
    }

    void runDrag(std::vector<PhysicsCircles*> &circles)
    {
        for(size_t i = 0;  i < circles.size(); i++)
            if(circles.at(i)->velocity.speed <= dragMinimum)
                circles.at(i)->velocity.speed = 0;
            else
                circles.at(i)->velocity.speed -= dragMinimum + (dragCoefficient * circles.at(i)->velocity.speed);
    }

    void runCollisionBox(std::vector<PhysicsCircles*> &circles)   //Collisions with boudingBox
    {
        for(size_t i = 0;  i < circles.size(); i++)
        {
            if((circles.at(i)->getPosition().y + circles.at(i)->getRadius()) >= boundingBox.bottom)
            {
                circles.at(i)->velocity.direction = getCollisionAngle(circles.at(i)->velocity.direction, 270.f);
                circles.at(i)->velocity.speed = runCollisionDrag(circles.at(i)->velocity.speed);
            }

            if((circles.at(i)->getPosition().x - circles.at(i)->getRadius()) <= boundingBox.left)
            {
                circles.at(i)->velocity.direction = getCollisionAngle(circles.at(i)->velocity.direction, 0.f);
                circles.at(i)->velocity.speed = runCollisionDrag(circles.at(i)->velocity.speed);
            }

            if((circles.at(i)->getPosition().x + circles.at(i)->getRadius()) >= boundingBox.right)
            {
                circles.at(i)->velocity.direction = getCollisionAngle(circles.at(i)->velocity.direction, 180.f);
                circles.at(i)->velocity.speed = runCollisionDrag(circles.at(i)->velocity.speed);
            }
        }
    }
    void runCollisions(std::vector<PhysicsCircles*> &circles/*,std::vector<sf::Shapes*> colliders*/)
    {
        for(size_t i = 0;  i < circles.size(); i++)
        {
            if(circles.at(i)->getPosition().y - circles.at(i)->getPosition().x + circles.at(i)->getRadius() >= 300)
            {
                circles.at(i)->velocity.direction = getCollisionAngle(circles.at(i)->velocity.direction, 315.f);
                circles.at(i)->velocity.speed = runCollisionDrag(circles.at(i)->velocity.speed);
            }

            if(circles.at(i)->getPosition().x + circles.at(i)->getPosition().y + circles.at(i)->getRadius() >= 400+ windowW)
            {
                circles.at(i)->velocity.direction = getCollisionAngle(circles.at(i)->velocity.direction, 225.f);
                circles.at(i)->velocity.speed = runCollisionDrag(circles.at(i)->velocity.speed);
            }
        }
    }
    void runSelfCollisions(std::vector<PhysicsCircles*> &circles)
    {
        for(size_t first = 0; first < circles.size(); first++)
        {
            for(size_t second = first + 1; second < circles.size() ;second++)
            {
                if(circles.at(first)->physicsOn && circles.at(second)->physicsOn) //if both circle have physics turned on
                {
                    if((sqrt(pow(circles.at(second)->getPosition().x - circles.at(first)->getPosition().x, 2)
                            + pow(circles.at(second)->getPosition().y - circles.at(first)->getPosition().y, 2)))
                            <= circles.at(first)->getRadius() + circles.at(second)->getRadius())   //if distance between two circles is less than their combined radii, a collision has occured
                    {
                        //gets the normal, i.e direction from first circle to second circle..
                        float normal = MyVelocity::getVelocityAngle(circles.at(second)->getPosition() - circles.at(first)->getPosition());

                        //sets the result directions
                        circles.at(first)->velocity.direction = getCollisionAngle(circles.at(first)->velocity.direction, reverseAngle(normal));
                        circles.at(second)->velocity.direction = getCollisionAngle(circles.at(second)->velocity.direction, normal);

                        //sets the result speeds
                        //
                        float forceTotal = circles.at(first)->velocity.speed * circles.at(first)->weight +
                                            circles.at(second)->velocity.speed * circles.at(second)->weight;

                        circles.at(first)->velocity.speed = forceTotal / 2 / circles.at(first)->weight;
                        circles.at(second)->velocity.speed = forceTotal / 2 / circles.at(second)->weight;

                        //runs collision drag on both circls
                        circles.at(first)->velocity.speed = runCollisionDrag(circles.at(first)->velocity.speed);
                        circles.at(second)->velocity.speed = runCollisionDrag(circles.at(second)->velocity.speed);
                    }
                }
            }
        }
    }


    float runCollisionDrag(float speed)
    {
        speed -= collisionDrag;
        if(speed < collisionDragMin)
            speed = 0.f;

        return speed;
    }

    //collide format i want.
    //void collide(obj, collideLine)
    //  getcollisionangle
    //  add collision drag
    //  getcollisionspeed
    //  change obj velocity accordingly
    //}



    void update(std::vector<PhysicsCircles*> &circles) //Temporarily passing in vector of circles, thoug in the future it could loop through all physics enitities.
    {
        runGravity(circles);
        runDrag(circles);
        runCollisionBox(circles);
        runCollisions(circles/*,colliders*/);
        runSelfCollisions(circles);


        for(size_t i = 0;  i < circles.size(); i++)
            circles.at(i)->update();
    }
};
