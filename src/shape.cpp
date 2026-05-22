#include "shape.hpp"
//  Update the position using speed and time (Distance = Speed * Time)
void shape::update(float deltaTime)
{
    position.x += speed.x * deltaTime;
    position.y += speed.y * deltaTime;
}

//  Return the current position
Vector2f shape::getPosition() const
{
    return position;
}

//  Set a new position
void shape::setPosition(Vector2f pos)
{
    position = pos;
}

//  Return the current speed
Vector2f shape::getSpeed() const
{
    return speed;
}

//  Set a new speed
void shape::setSpeed(Vector2f sp)
{
    speed = sp;
}
