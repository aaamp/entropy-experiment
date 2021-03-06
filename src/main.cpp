#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "particle.h"
#include "symul.h"
#include "displ.hpp"
#include <random>
#include <chrono>
#include "entropy.h"
#include "lineChart.hpp"

int main()
{
    // number of particles
    const int PAR_N = 1000;

    // box size
    // upper left corner of the box is at (0, 0)
    // bottom right at BOX_XY
    const vec2f BOX_XY(200, 200);

    // box in which particles start
    // from (0, 0) to BOX_S
    const vec2f BOX_S(20, 20);

    // particle radius
    const float RAD = 0.2;

    // speed of a particle at the start is chosen randomly from
    // { (x, y) : x, y \in [-SPEED, SPEED] }
    const float SPEED = 0.3;


    displ display(RAD, BOX_XY);
    display.createWindow("Symulacja");
    

    symul symulation = symul(PAR_N, RAD, BOX_XY, BOX_S, SPEED, 0.17);
    std::vector<particle> particles = symulation.getParticles();

    entropy ent(BOX_XY.getX() / 10, SPEED / 3, 10, 6, SPEED, particles.size());

    chart chart2D;
    chart2D.createWindow(800, 400, "Wykres entropii od czasu");
    chart2D.chartReDraw();

    auto lastTime = std::chrono::high_resolution_clock::now();
    for(int tick = 0; tick < 100000; tick++)
    {
        std::cout << "tick " << tick << std::endl;

        /*if(tick > 0)  
          std::this_thread::sleep_until(lastTime + std::chrono::milliseconds(100));
          lastTime = std::chrono::high_resolution_clock::now();*/

        particles = symulation.getParticles();

        std::future<void> symulTask = std::async(std::launch::async, [&symulation]() {
            symulation.moveParticles();
        });

        std::future<double> entropyTask = std::async(std::launch::async, [&ent, &particles]() {
            ent.ClearBoxes();
            ent.GroupParticles(&particles);
            return ent.calcEntropy();
        });

        display.drawParticles(particles);
        display.pollEvents();

        chart2D.chartReDraw();
        chart2D.pollEvents();

        while (symulTask.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready
            || entropyTask.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready)
        {
            display.drawParticles(particles);
            display.pollEvents();
            chart2D.chartReDraw();
            chart2D.pollEvents();
        }

        double e = entropyTask.get();
        std::cout << "Entropy: " << e << std::endl;

        chart2D.chartUpdate(tick, e);

    }
}

