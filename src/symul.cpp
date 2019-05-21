
#include "symul.h"
#include <iostream>
#include <thread>
#include <random>
#include <algorithm>
#include <ctime>
#include <cmath>

const std::vector<particle>& symul::moveParticles()
{
    using posind = std::vector<std::pair<vec2f, int>>; 

    // number of threads = number of buckets
    // todo experiment with this
    // should depend on number of particles and box size somehow
    const int thrn = 15;

    // put positions in thrn buckets by their Y
    float buckLen = box.getY() / thrn;
    std::vector<posind> splited(thrn);
    for(auto& i : splited)
        i.reserve(particles.size() * 2 / thrn);
    for(int i = 0; i < particles.size(); i++)
    {
        int mybucket = static_cast<int>(std::floor(particles[i].getPosition().getY() / buckLen));
        if(mybucket < 0)
            mybucket = 0;
        if(mybucket >= thrn)
            mybucket = thrn;
        splited[mybucket].push_back(std::make_pair(particles[i].getPosition(), i));
        if(mybucket > 0 && particles[i].getPosition().getY() - (buckLen * mybucket) < 2 * particleR)
            splited[mybucket - 1].push_back(splited[mybucket].back());
        //if(mybucket < thrn - 1 && (mybucket + 1) * buckLen - particles[i].getPosition().getY() < 2 * particleR)
            //splited[mybucket + 1].push_back(splited[mybucket].back());
    }

    // function that returns collisions from one bucket
    auto getCollisions = [&](int b)
    {
        std::vector<std::pair<int, int>> myCollisions;    
        myCollisions.reserve(particles.size() * 2 / thrn);

        std::sort(splited[b].begin(), splited[b].end(), [](auto x, auto y)
        { 
            return x.first.getX() < y.first.getX();
        });

        auto startj = splited[b].begin();
        for(auto i = splited[b].begin(); i < splited[b].end(); i++)
        {
            while(startj < i && startj->first.getX() < i->first.getX() - particleR * 2)
                startj++;
            for(auto j = startj; j < i; j++)
            {
                if((j->first - i->first).getLength() < 2 * particleR)
                    myCollisions.push_back(std::make_pair(i->second, j->second));
            }
        }
        return myCollisions;
    };

    // get collisions
    std::vector<std::future<std::vector<std::pair<int, int>>>> futures(thrn);
    for(int i = 0; i < thrn; i++)
    {
        futures[i] = std::async(std::launch::async, getCollisions, i);
    }

    // get collisions in one vector
    std::vector<std::pair<int, int>> collisions;
    for(int i = 0; i < thrn; i++)
    {
        auto bcoll = futures[i].get();
        collisions.insert(collisions.end(), bcoll.begin(), bcoll.end());
    }

    // shuffle collisions
    std::shuffle(collisions.begin(), collisions.end(), mt_rand);

    // apply collisions
    for(auto& i : collisions)
        particles[i.first].collideWith(particles[i.second]);
    
    // collide with box
    for(auto& i : particles)
        i.collideBox(box, particleR);

    // update position
    for(auto& p : particles)
        p.update(timeTick);

    //std::cerr << "collisions: " << collisions.size() << std::endl;

    return particles;
}


symul::symul(const int& n, const float& r, const vec2f& boxS, const vec2f& iniBox, float speed, float time)
    : particleR(r), box(boxS), particles(n), timeTick(time), mt_rand(std::time(0))
{
    auto randFloat = [&](float low, float high)
    {
        return low + (high - low) * (static_cast<float>(mt_rand() - mt_rand.min()) / static_cast<float>(mt_rand.max()));
    };
    for(int i = 0; i < n; i++)
        particles[i] = particle(vec2f(randFloat(0 + r, iniBox.getX() - r), randFloat(0 + r, iniBox.getY() - r)),
                                vec2f(randFloat(-speed, speed), randFloat(-speed, speed)));
}

