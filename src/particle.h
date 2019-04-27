#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "vec2.h"

class particle
{
public:
    particle(const vec2f& Position, const vec2f& Velocity, float Mass)
        : position(Position), velocity(Velocity), mass(Mass) {}
    float getEnergy() const { return mass * velocity.getSquaredLength() / 2; }
    const vec2f& getPosition() const { return position; }
    const vec2f& getVelocity() const { return velocity; }
    const float& getMass() const { return mass; }
    void update(float timeTick) { position += velocity*timeTick; }
private:
    vec2f position, velocity;
    float mass;
};

#endif
