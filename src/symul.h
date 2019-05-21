#ifndef SYMUL_H_
#define SYMUL_H_

#include <vector>
#include <thread>
#include <chrono>
#include <future>
#include <random>
#include "vec2.h"
#include "particle.h"


class symul
{
public:
    symul(const int& n, const float& r, const vec2f& boxSize, const vec2f& initialBox, float speed, float time = 0.1);

    const std::vector<particle>& getParticles() const { return particles; }
    const vec2f& getBox() const { return box; }
    const float& getParticleR() { return particleR; }

    const std::vector<particle>& moveParticles();

private:
    std::vector<particle> particles;

    std::mt19937 mt_rand;
    vec2f box;
    float particleR;
    float timeTick;
};


#endif
