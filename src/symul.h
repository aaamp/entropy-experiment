#ifndef SYMUL_H_
#define SYMUL_H_

#include <vector>
#include <thread>
#include <chrono>
#include <future>
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

    // move particles by given time
    // also spawns new thread where it will check for collisions
    const std::vector<particle>& moveParticles(const float& timeTick);


private:
    std::vector<particle> particles;
    vec2f box;
    float particleR;

    std::future<std::vector<particle>> afterCollisions;
    static std::vector<particle> collide(std::vector<particle> fparticles);
};


#endif
