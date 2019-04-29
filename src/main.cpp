#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "particle.h"
#include "symul.h"
#include "displ.hpp"

int main()
{
	displ display(0.1);
	display.createWindow("Symulacja", 800, 600);
	display.zoom(0.01);
	display.setCenter(2,2);

    symul symulation = symul(2, 0.1, vec2f(200, 100), vec2f(100, 100), 0.2);

    for(int tick = 0; tick < 4; tick++)
    {
        std::cout << "tick " << tick << std::endl;
        for(auto i : symulation.getParticles())
            std::cout << i.getPosition() << std::endl;
        std::cout << std::endl;
		
		display.drawParticles(symulation.getParticles());

		std::future<void> task = std::async(std::launch::async, [&symulation]() {
            symulation.moveParticles(0.1);
        });
        while (task.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready)
            display.pollEvents();

    }
}

