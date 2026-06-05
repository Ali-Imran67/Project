#include "ball.hpp"
#include <cmath>

Ball::Ball(sf::Vector2f initialPos, float radius, sf::Vector2f initialSpeed)
    : shape(initialPos, initialSpeed)
{
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin({radius, radius}); // setting the ball center at origin
}

void Ball::draw(sf::RenderWindow& window)
{
    circle.setPosition(position); // making sure that what we DRAW is at the same place as what we're CALCULATING (the circle/ball)
    window.draw(circle);
}

void Ball::checkCollisions(sf::FloatRect leftPaddleBounds, sf::FloatRect rightPaddleBounds, SoundManager& sfx)
{
    float radius = circle.getRadius();

    float upperLimit = 60.f; //boundaries
    float lowerLimit = 660.f;

    if (position.y - radius <= upperLimit)
    {
        position.y = upperLimit + radius;
        speed.y = std::abs(speed.y);      // force the ball to bounce downward
        sfx.play("Impact", 100.f);
    }
    else if (position.y + radius >= lowerLimit)
    {
        position.y = lowerLimit - radius;
        speed.y = -abs(speed.y);     // force the ball to bounce upwards
        sfx.play("Impact", 100.f);
    }

    // here we check if ball collided with paddles
    FloatRect ballBounds = getGlobalBounds();

    // left side
    if (ballBounds.findIntersection(leftPaddleBounds))
    {
        position.x = leftPaddleBounds.position.x + leftPaddleBounds.size.x + radius; // push out of paddle
        speed.x = abs(speed.x); // force the ball to move right
        speed *= 1.05f;              // this makes sure the ball keeps increasing in speed
        sfx.play("Impact", 100.f);
    }
    // right side
    else if (ballBounds.findIntersection(rightPaddleBounds))
    {
        position.x = rightPaddleBounds.position.x - radius;
        speed.x = -abs(speed.x); // ball goes left
        speed *= 1.05f;              
        sfx.play("Impact", 100.f);
    }
}

FloatRect Ball::getGlobalBounds() const
{
    float r = circle.getRadius();
    // Computes top-left corner using center point configuration
    return FloatRect({position.x - r, position.y - r}, {r * 2.f, r * 2.f});
}

float Ball::getRadius() const
{
    return circle.getRadius();
}