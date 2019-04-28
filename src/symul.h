#ifndef SYMUL_H_
#define SYMUL_H_

#include <vector>
#include "vec2.h"
#include "particle.h"


class symul
{
public:

	// new symulation with n particles with radius r
	// code inside is temporary
	symul(const int& n, const float& r, const vec2f& boxSize, const vec2f& initialBox, const float& maxspeed);

	const std::vector<particle>& getParticles() const { return particles; }
	const vec2f& getBox() const { return box; }
	const float& getParticleR() { return particleR; }

	const std::vector<particle>& moveParticles(const float& timeTick);

	const std::vector<particle>& asyncPrepareMove(const float& timeTick);

	const std::vector<particle>& swapPrepared();

private:
	std::vector<particle> particles, futureParticles;
	vec2f box;
	float particleR;
};


#endif
