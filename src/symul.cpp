
#include "symul.h"
#include <iostream>
#include <thread>
#include <random>
#include <algorithm>
#include <ctime>

const std::vector<particle>& symul::moveParticles()
{
    sort(particles.begin(), particles.end(), [](auto x, auto y)
    { 
        return x.getPosition().getX() < y.getPosition().getX();
    });

    auto startj = particles.begin();
    for(auto i = particles.begin(); i < particles.end(); i++)
    {
        while(startj <= i && startj->getPosition().getX() < i->getPosition().getX() - particleR * 2)
            startj++;
        i->collideBox(box, particleR);
        for(auto j = startj; j < i; j++)
            if((i->getPosition() - j->getPosition()).getLength() < 2 * particleR)
                i->collideWith(*j);
    }

    for(auto& p : particles)
        p.update(timeTick);

    return particles;
}


symul::symul(const int& n, const float& r, const vec2f& boxS, const vec2f& iniBox, float maxspeed, float time)
    : particleR(r), box(boxS), particles(n), timeTick(time) 
{
    std::mt19937 mt_rand(std::time(0));
    auto randFloat = [&](float low, float high)
    {
        return low + (high - low) * (static_cast<float>(mt_rand() - mt_rand.min()) / static_cast<float>(mt_rand.max()));
    };
    for(int i = 0; i < n; i++)
        particles[i] = particle(vec2f(randFloat(0 + r, iniBox.getX() - r), randFloat(0 + r, iniBox.getY() - r)),
                                vec2f(randFloat(-maxspeed, maxspeed), randFloat(-maxspeed, maxspeed)));
}

