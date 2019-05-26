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
    // number of particles
    const int PAR_N = 50000;

    // box size
    // upper left corner of the box is at (0, 0)
    // bottom right at BOX_XY
    const vec2f BOX_XY(200, 200);

    // box in which particles start
    // from (0, 0) to BOX_S
    const vec2f BOX_S(100, 100);

    // particle radius
    const float RAD = 0.2;

    // speed of a particle at the start is chosen randomly from
    // { (x, y) : x, y \in [-SPEED, SPEED] }
    const float SPEED = 0.3;



    displ display(RAD, BOX_XY);
    display.createWindow("Symulacja");
    
    symul symulation = symul(PAR_N, RAD, BOX_XY, BOX_S, SPEED);
    std::vector<particle> particles = symulation.getParticles();

    entropy ent(BOX_XY.getX() / 20, SPEED / 2, 40, 4, SPEED, particles.size());

    auto lastTime = std::chrono::high_resolution_clock::now();
    for(int tick = 0; tick < 100000; tick++)
    {
        std::cout << "tick " << tick << std::endl;

        /*if(tick > 0)  
          std::this_thread::sleep_until(lastTime + std::chrono::milliseconds(100));
          lastTime = std::chrono::high_resolution_clock::now();*/

        // To czy szybsza jest fizyka czy grafika zależy aktualnie od powiększenia obrazu,
        // fizyka nie powoduje lagów.

        particles = symulation.getParticles();

        std::future<void> symulTask = std::async(std::launch::async, [&symulation]() {
            symulation.moveParticles();
        });

        std::future<double> entropyTask = std::async(std::launch::async, [&ent, &particles]() {
            ent.ClearBoxes();
            ent.GroupParticles(&particles);
            return ent.calcEntropy();
            //double probability = pow(exp(1), entropy); //nie wiem, czy jest Wam to do szczęścia potrzebne, feel free to comment
        });

        display.drawParticles(particles);
        display.pollEvents();

        while (symulTask.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready
            || entropyTask.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready)
        {
            display.drawParticles(particles);
            display.pollEvents();
        }

        double e = entropyTask.get();
        std::cout << "Entropy: " << e << std::endl;
    }
}

