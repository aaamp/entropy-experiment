
#include "symul.h"
#include <iostream>
#include <thread>
#include <random>
#include <algorithm>
#include <ctime>

const std::vector<particle>& symul::moveParticles()
{
    //update sorted positions
    for(auto& i : sortedPositions)
        i.first = particles[i.second].getPosition();

    sort(sortedPositions.begin(), sortedPositions.end(), [](auto x, auto y)
    { 
        return x.first.getX() < y.first.getX();
    });

    long long checkCount = 0;

    std::vector<std::pair<int, int>> collisions;
    auto startj = sortedPositions.begin();
    for(auto i = sortedPositions.begin(); i < sortedPositions.end(); i++)
    {
        while(startj <= i && startj->first.getX() < i->first.getX() - particleR * 2)
            startj++;
        for(auto j = startj; j < i; j++)
        {
            checkCount++;
            if((j->first - i->first).getLength() < 2 * particleR)
                collisions.push_back(std::make_pair(i->second, j->second));
        }
    }

    int collCount = collisions.size(); 

    random_shuffle(collisions.begin(), collisions.end(), [&](int n){return mt_rand() % n;});

    for(auto& i : collisions)
        particles[i.first].collideWith(particles[i.second]);

    for(auto& i : particles)
        i.collideBox(box, particleR);

    for(auto& p : particles)
        p.update(timeTick);

    std::cerr << "collisions: " << collCount << std::endl;
    std::cerr << "checks: " << checkCount << std::endl;

    return particles;
}


symul::symul(const int& n, const float& r, const vec2f& boxS, const vec2f& iniBox, float maxspeed, float time)
    : particleR(r), box(boxS), particles(n), timeTick(time), sortedPositions(n), mt_rand(std::time(0))
{
    auto randFloat = [&](float low, float high)
    {
        return low + (high - low) * (static_cast<float>(mt_rand() - mt_rand.min()) / static_cast<float>(mt_rand.max()));
    };
    for(int i = 0; i < n; i++)
        particles[i] = particle(vec2f(randFloat(0 + r, iniBox.getX() - r), randFloat(0 + r, iniBox.getY() - r)),
                                vec2f(randFloat(-maxspeed, maxspeed), randFloat(-maxspeed, maxspeed)));

    for(int i = 0; i < n; i++)
        sortedPositions[i] = std::make_pair(particles[i].getPosition(), i);
}

