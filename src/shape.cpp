#include "shape.hpp"

void shape::update(float deltaTime)
{
    position.x += speed.x * deltaTime;
    position.y += speed.y * deltaTime;
}


Vector2f shape::getPosition() const
{
    return position;
}


void shape::setPosition(Vector2f pos)
{
    position = pos;
}


Vector2f shape::getSpeed() const
{
    return speed;
}


void shape::setSpeed(Vector2f sp)
{
    speed = sp;
}
