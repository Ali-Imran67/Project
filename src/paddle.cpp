#include "paddle.hpp"


Paddle::Paddle(Vector2f initialPos, Vector2f initialSpeed, float width, float height)
    : shape(initialPos, initialSpeed), width(width), height(height)
{
    rect.setSize(Vector2f(width, height));
    rect.setPosition(initialPos);
    rect.setFillColor(sf::Color::White);
}

void Paddle::draw(RenderWindow& window)
{
    rect.setPosition(position);   // sync SFML rect with our position
    window.draw(rect);
}

// Moves paddle and clamps it so it never leaves the window vertically
void Paddle::update(float deltaTime)
{
    shape::update(deltaTime);

    if (position.y < 0.f)
    {
        position.y = 0.f;
        speed.y = 0.f;
    }
}


// call this when the player presses UP / W
void Paddle::moveUp(float deltaTime, float upperlimit)
{
    position.y -= speed.y * deltaTime;

    if (position.y < upperlimit)
        position.y = upperlimit;
}

// call this when the player presses DOWN / S
void Paddle::moveDown(float deltaTime, float lowerlimit)
{
    position.y += speed.y * deltaTime;

    if (position.y + height > lowerlimit)
        position.y = lowerlimit - height;
}


float Paddle::getWidth()  const { return width;  }
float Paddle::getHeight() const { return height; }

sf::FloatRect Paddle::getBounds() const
{
    return rect.getGlobalBounds();   // used by ball for collision check
}
