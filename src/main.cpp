#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "particle.h"
#include "symul.h"
#include "displ.hpp"
#include <random>
#include <chrono>
#include "entropy.h"

int main()
{
    displ display(0.2, vec2f(200, 100));
    display.createWindow("Symulacja", 1000, 500);
    display.zoom(0.2);
    display.setCenter(100,50);

    symul symulation = symul(50000, 0.2, vec2f(200, 100), vec2f(100, 100), 0.3, 0.1);
    std::vector<particle> particicles = symulation.getParticles();

    entropy ent(2, 2, 5, 4, 5, 4);

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
        ent.LoadParticles(particicles);
        ent.GroupParticles();
        double entropy = ent.calcEntropy();
        double probability = pow(exp(1), entropy); //nie wiem, czy jest Wam to do szczęścia potrzebne, feel free to comment
        vector<vector< vector<vector<int>>>>a = ent.GetBoxes();
        ent.ClearBoxes();

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

