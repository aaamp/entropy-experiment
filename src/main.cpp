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

    particle x2({0,0},{3,2});
    particle y({6,0},{1,3});
    x2.collideWith(y);
    std::cout << x2.getVelocity() << " " << y.getVelocity() << std::endl;

    symul symulation = symul(2, 0.1, vec2f(200, 100), vec2f(100, 100), 0.2);

    for(int tick = 0; tick < 4; tick++)
    {
        std::cout << "tick " << tick << std::endl;
        for(auto i : symulation.getParticles())
            std::cout << i.getPosition() << std::endl;
        std::cout << std::endl;

        symulation.moveParticles(1);
    }
}

