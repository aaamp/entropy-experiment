
#include "symul.h"
#include <iostream>
#include <thread>

const std::vector<particle>& symul::moveParticles(const float& timeTick)
{
    particles = afterCollisions.get();

    for(auto& p : particles)
        p.update(timeTick);

    afterCollisions = std::async(std::launch::async, collide, particles);

    return particles;
}

std::vector<particle> symul::collide(std::vector<particle> fparticles)
{
    // todo collisions 

    // temporary, just to simulate this being the most time consuming part of the whole thing
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return fparticles;
}

symul::symul(const int& n, const float& r, const vec2f& boxS, const vec2f& iniBox, const float& maxspeed)
    : particleR(r), box(boxS), particles(n) 
{
    // todo random particles in proper box
    for(int i = 0; i < n; i++)
        particles[i] = particle(vec2f(i, i), vec2f(maxspeed, -maxspeed));

    afterCollisions = std::async(std::launch::async, collide, particles);
}

