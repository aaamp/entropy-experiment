#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "particle.h"
#include "symul.h"

int main()
{
    particle x({1,1},{2,2});
    x.update(1);
    std::cout << x.getPosition() << std::endl;

    symul symulation = symul(2, 0.1, vec2f(200, 100), vec2f(100, 100), 0.2);

    for(int tick = 0; tick < 10; tick++)
    {
        std::thread th(&symul::asyncPrepareMove, &symulation, 1);

        std::cout << "tick " << tick << std::endl;
        for(auto i : symulation.getParticles())
            std::cout << i.getPosition().getX() << ' ' << i.getPosition().getY() << std::endl;
        std::cout << std::endl;

        th.join();
        symulation.swapPrepared();
    }

}
