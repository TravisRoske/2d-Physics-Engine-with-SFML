#include <SFML/System.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>


//mutexes apparantly don't work...



sf::Mutex mutex;  //Blocks other threads from accessing same resources while it's running

void func()
{
    sf::Lock lock(mutex);
   // sf::Lock lock(mutex);//Locks the mutex so it will release whn out of scope.

   for(int i = 0; i<10; i++){
        srand(time(NULL));

        switch(rand()%6){
        case 0:
            std::cout << "Fucking fuck0" << std::endl;

        case 1:
            std::cout << "Fucking fuck1"<< std::endl;

        case 2:
            std::cout << "Fucking fuck2"<< std::endl;

        case 3:
            std::cout << "Fucking fuck3"<< std::endl;
        case 4:
            std::cout << "Fucking fuck4"<< std::endl;
        case 5:
            std::cout << "Fucking fuck5"<< std::endl;

        }
        sf::sleep(sf::milliseconds(500));
   }

   return;
}

int main()
{
    // create a thread with func() as entry point
    sf::Thread thread(&func);

    // run it
    thread.launch();

    sf::sleep(sf::milliseconds(1500));
    // the main thread continues to run...

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm the main thread" << std::endl;

    return 0;
}
