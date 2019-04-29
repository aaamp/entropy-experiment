
#include "symul.h"
#include <iostream>
#include <thread>
#include <random>

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

    return fparticles;
}

symul::symul(const int& n, const float& r, const vec2f& boxS, const vec2f& iniBox, const float& maxspeed)
    : particleR(r), box(boxS), particles(n) 
{
	std::mt19937 mt_rand(time(0));
	auto randFloat = [&](float low, float high)
	{
		return low + (high - low) * (static_cast<float>(mt_rand()) / static_cast<float>(mt_rand.max()));
	};
    for(int i = 0; i < n; i++)
		particles[i] = particle(vec2f(randFloat(0, iniBox.getX()), randFloat(0, iniBox.getY())),
							    vec2f(randFloat(-maxspeed, maxspeed), randFloat(-maxspeed, maxspeed)));

    afterCollisions = std::async(std::launch::async, collide, particles);
}

