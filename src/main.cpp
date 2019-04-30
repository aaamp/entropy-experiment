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
    displ display(0.2);
    display.createWindow("Symulacja",1000,500);
    display.zoom(0.2);
    display.setCenter(100,50);


    symul symulation = symul(50000, 0.2, vec2f(200, 100), vec2f(100, 100), 0.3);
    std::vector<particle> particicles = symulation.getParticles();

    auto lastTime = std::chrono::high_resolution_clock::now();
    for(int tick = 0; tick < 100000; tick++)
    {
        std::cout << "tick " << tick << std::endl;
        /*
       std::cout << "tick " << tick << std::endl;
       for(auto i : symulation.getParticles())
           std::cout << i.getPosition() << std::endl;
       std::cout << std::endl;
       */

        /*if(tick > 0)		
            std::this_thread::sleep_until(lastTime + std::chrono::milliseconds(100));
        lastTime = std::chrono::high_resolution_clock::now();*/

        // To czy szybsza jest fizyka czy grafika zależy aktualnie od powiększenia obrazu,
        // fizyka nie powoduje lagów.

        particicles = symulation.getParticles();
        std::future<void> task = std::async(std::launch::async, [&symulation]() {
            symulation.moveParticles();
        });
        
        display.drawParticles(particicles);
        display.pollEvents();
        while (task.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready)
        {
            display.drawParticles(particicles);
            display.pollEvents();
        }
    }
}

