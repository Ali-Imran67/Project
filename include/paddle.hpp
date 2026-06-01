#pragma once
#include "shape.hpp"

class Paddle : public shape {

private:
    float width;
    float height;
    sf::RectangleShape rect;   // SFML drawable rectangle

public:
    // Constructor
    Paddle(Vector2f initialPos, Vector2f initialSpeed, float width, float height);

    // Override pure virtual draw() from shape
    void draw(RenderWindow& window) override;

    // Override update() to add boundary clamping
    void update(float deltaTime) override;

    // Move paddle up/down manually
    void moveUp(float deltaTime, float upperlimit);
    void moveDown(float deltaTime, float lowerlimit);

    // Getters for collision detection 
    float getWidth()  const;
    float getHeight() const;

    // Returns the SFML rect (used for collision in game loop)
    sf::FloatRect getBounds() const;
};
