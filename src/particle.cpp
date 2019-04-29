
#include "particle.h"


void particle::collideWith(particle& other)
{
    vec2f direction = (position - other.position).getNormalized();
    vec2f::floatingType changeSpeed = (velocity - other.velocity) * direction;
    if(changeSpeed < 0)
    {
        vec2f change = changeSpeed * direction;
        velocity -= change;
        other.velocity += change;
    }
}

void particle::collideBox(const vec2f& box, const float& r)
{
    if((position.getX() < 0 + r && velocity.getX() < 0)
       || (position.getX() > box.getX() - r && velocity.getX() > 0))
        velocity.setX(-velocity.getX());
    if((position.getY() < 0 + r && velocity.getY() < 0)
       || (position.getY() > box.getY() - r && velocity.getY() > 0))
        velocity.setY(-velocity.getY());
}
