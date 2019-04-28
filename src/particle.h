#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "vec2.h"

class particle
{
public:
    particle()
        : position(vec2f(0, 0)), velocity(vec2f(0, 0)) {}
    particle(const vec2f& Position, const vec2f& Velocity)
        : position(Position), velocity(Velocity) {}
    float getEnergy() const { return velocity.getSquaredLength() / 2; }
    const vec2f& getPosition() const { return position; }
    const vec2f& getVelocity() const { return velocity; }
    void update(float timeTick) { position += velocity*timeTick; }
    void collideWith(particle& other);
private:
    vec2f position, velocity;
};

#endif
