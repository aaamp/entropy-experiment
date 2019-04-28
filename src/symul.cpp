
#include "symul.h"
#include <iostream>

const std::vector<particle>& symul::moveParticles(const float& timeTick)
{
	asyncPrepareMove(timeTick);
	return swapPrepared();
}

const std::vector<particle>& symul::asyncPrepareMove(const float& timeTick)
{
	futureParticles = particles;

	// todo actual symulation with collisions
	for(auto& p : futureParticles)
		p.update(timeTick);

	return futureParticles;
}

const std::vector<particle>& symul::swapPrepared()
{
	particles.swap(futureParticles);
	return particles;
}

symul::symul(const int& n, const float& r, const vec2f& boxS, const vec2f& iniBox, const float& maxspeed)
	: particleR(r), box(boxS), particles(n)
{
	// todo random particles
	for(int i = 0; i < n; i++)
	{
		particles[i] = particle(vec2f(i, i), vec2f(maxspeed, -maxspeed));
	}
}

