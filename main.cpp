#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <iostream>
#include <vector>

#include "Physics.h"
#include "PhysicsCircles.h"
#include "Values.h"


int main()
{
    //============Startup============
    sf::RenderWindow rwindow(sf::VideoMode(windowW, windowH), "Bounce Physics Engine");
    rwindow.setFramerateLimit(120);
    Physics physics;

    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("arrow.png"))
    {
        std::cout << "Error loading Texture\n";
    }
    arrowTexture.setSmooth(true);
    sf::Sprite *arrowSprite = nullptr;
    //===============================


    sf::RectangleShape rect(sf::Vector2f(1500.f, 10.f));
    rect.setRotation(45.f);
    rect.setFillColor(sf::Color::Black);
    rect.move(0.f, 320.f);

    sf::RectangleShape rect2(sf::Vector2f(1500.f, 10.f));
    rect2.setRotation(-45.f);
    rect2.setFillColor(sf::Color::Black);
    rect2.move(windowW - 630.f, windowH );



    std::vector<PhysicsCircles*> circles;
    //========Circle objects==========
    PhysicsCircles c1(45.0f, 10.0f, 210.f);
    c1.setOrigin(45.0f, 45.0f);
    c1.move(300.f,300.f);
    circles.push_back(&c1);
    c1.setFillColor(sf::Color::Black);

    PhysicsCircles c2(20.0f, 18.0f, 330.f);
    c2.setOrigin(20.0f, 20.0f);
    c2.move(400.f,400.f);
    circles.push_back(&c2);

    PhysicsCircles c3(40.0f, 10.0f, 180.f);
    c3.setOrigin(40.0f, 40.0f);
    c3.move(500.f,500.f);
    circles.push_back(&c3);

    PhysicsCircles c4(40.0f, 15.0f, 220.f);
    c4.setOrigin(40.0f, 40.0f);
    c4.move(400.f,0.f);
    circles.push_back(&c4);

    PhysicsCircles c5(40.0f, 15.0f, 20.f);
    c5.setOrigin(40.0f, 40.0f);
    c5.move(200.f,0.f);
    circles.push_back(&c5);

    PhysicsCircles c6(40.0f, 5.0f, 230.f);
    c6.setOrigin(40.0f, 40.0f);
    c6.move(300.f,200.f);
    circles.push_back(&c6);

    PhysicsCircles c7(60.0f, 1.0f, 20.f);
    c7.setOrigin(60.0f, 60.0f);
    c7.move(1000.f,100.f);
    circles.push_back(&c7);

    PhysicsCircles c8(15.0f, 10.0f, 270.f);
    c8.setOrigin(15.0f, 15.0f);
    c8.move(900.f,300.f);
    circles.push_back(&c8);


    int n = 0;
    for(size_t i = 1; i < circles.size(); i++)
    {
        circles.at(i)->setFillColor(sf::Color((100-n) % 230, (250+n) % 231, 50));
        n += 50;
    }

    //================================

    //==============================================================================
    //===============Game Loop======================================================
    float cirRadius = 10.f;
    bool wasPressed = false;
    sf::Vector2f newLoc;
    sf::Vector2f finalLoc;
    while(rwindow.isOpen())
    {
        sf::Event event;


        while(rwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rwindow.close();
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!wasPressed){      //if you just started the click
                newLoc.x = sf::Mouse::getPosition(rwindow).x;
                newLoc.y = sf::Mouse::getPosition(rwindow).y;
                cirRadius = 10.f;
                circles.push_back(new PhysicsCircles(cirRadius, 0.0f, 0.0f));
                circles.at(circles.size()-1)->physicsOn = false;
                circles.at(circles.size()-1)->setOrigin(cirRadius, cirRadius);
                circles.at(circles.size()-1)->setPosition(newLoc);
                circles.at(circles.size()-1)->deleteThis = true;
                wasPressed = true;
                //make the arrow
                delete arrowSprite;
                arrowSprite = new sf::Sprite(arrowTexture);
                arrowSprite->setColor(sf::Color(150, 150, 255, 128));
                arrowSprite->setOrigin(64,0);
                arrowSprite->setPosition(newLoc);
                arrowSprite->setScale(0,0);
            }
            else //if continuing to hold the mouse button
            {
                if(cirRadius < 80)
                    cirRadius += .3f;
                circles.at(circles.size()-1)->setRadius(cirRadius);
                circles.at(circles.size()-1)->setOrigin(cirRadius, cirRadius);
                circles.at(circles.size()-1)->setFillColor(sf::Color(cirRadius * 3, 255 - cirRadius*3, 50));
                //======================
                finalLoc.x = sf::Mouse::getPosition(rwindow).x;
                finalLoc.y = sf::Mouse::getPosition(rwindow).y;
                arrowSprite->setRotation(MyVelocity::getVelocityAngle(newLoc - finalLoc) + 90);
                float scale = getDistance(newLoc, finalLoc) / 512;
                scale = (scale > 1) ? 1 : scale;
                arrowSprite->setScale(scale, scale);

            }
        }
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && wasPressed){ //When you let go of mouse button
            wasPressed = false;
            circles.at(circles.size()-1)->weight = (3.1415 * pow(cirRadius, 2));
            circles.at(circles.size()-1)->physicsOn = true;
            finalLoc.x = sf::Mouse::getPosition(rwindow).x;
            finalLoc.y = sf::Mouse::getPosition(rwindow).y;
            circles.at(circles.size()-1)->velocity.direction = MyVelocity::getVelocityAngle(newLoc - finalLoc);

            float speed = getDistance(newLoc, finalLoc) / 512; //This is to make it scale the same as the arrow
            speed = (speed > 1) ? 1 : speed;
            circles.at(circles.size()-1)->velocity.speed = speed * 52;
            //Delete the arrow
           delete arrowSprite;
           arrowSprite = nullptr;
        }


        rwindow.clear(sf::Color::White);

        physics.update(circles);

        for(size_t i = 0; i < circles.size(); i++)
        {
            rwindow.draw(*(circles.at(i)));
        }
        rwindow.draw(rect);
        rwindow.draw(rect2);
        if(arrowSprite != nullptr)
            rwindow.draw(*arrowSprite);


        rwindow.display();
    }



    //==============Cleanup================================================================
    for(size_t i = 0; i < circles.size(); i++){
        if(circles.at(i)->deleteThis)
            delete circles.at(i);
    }

    return 0;
}



//Collisions
//If the center of a circle is =< radius away from another object.....or <= radius away from the bounding box of the window,
//Zero out the velocities
//Then apply a force to both objects



//Bounding box
//down
//left
//right
//All have position, and normals.



//Vectorlist of circles
//Vectorlist of static obects


//Every frame, each object calculates all collisions.
//circle checks position against all collidable objects.
//If collision occurs, pass in the objects to a collision function and apply the resultance vector to each....
//I.e  with boudning box pass in the normal and the vector of circle, then change vector of circle to after...


//Drag
//Decrease each velocity closer to absolute 0 by a small amount every frame
//

//Gravity
//

//Update Loction based on location and veloctiy.

