
#include "particle.h"


void particle::collideWith(particle& other)
{
    vec2f direction = (getPosition() - other.getPosition()).getNormalized();
    vec2f change = ((getVelocity() - other.getVelocity()) * direction) * direction;
    velocity -= change;
    other.velocity += change;
}
