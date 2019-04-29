#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "particle.h"
#include "symul.h"
#include "displ.hpp"
#include <random>
#include <chrono>


int main()
{
    displ display(2);
    display.createWindow("Symulacja",1000,500);
    display.zoom(0.2);
    display.setCenter(100,50);

    std::mt19937 mt_rand(time(0));
    std::cout << mt_rand.max() << std::endl;
    std::cout << mt_rand.min() << std::endl;

    particle x({1,1},{2,2});
    x.update(1);
    std::cout << x.getPosition() << std::endl;

    particle x2({0,0},{3,2});
    particle y({6,0},{1,3});
    x2.collideWith(y);
    std::cout << x2.getVelocity() << " " << y.getVelocity() << std::endl;

    symul symulation = symul(100, 2, vec2f(200, 100), vec2f(100, 100), 0.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    for(int tick = 0; tick < 1000; tick++)
    {
        /*
       std::cout << "tick " << tick << std::endl;
       for(auto i : symulation.getParticles())
           std::cout << i.getPosition() << std::endl;
       std::cout << std::endl;
       */

        if(tick > 0)		
            std::this_thread::sleep_until(lastTime + std::chrono::milliseconds(100));
        lastTime = std::chrono::high_resolution_clock::now();
        symulation.moveParticles(1);

        display.drawParticles(symulation.getParticles());
    }
}

