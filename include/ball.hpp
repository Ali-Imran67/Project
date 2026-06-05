#pragma once
#include "shape.hpp"
#include "audio.hpp"

class Ball : public shape {
private:
    CircleShape circle;

public:
    Ball(Vector2f initialPos, float radius, Vector2f initialSpeed);

    void draw(RenderWindow& window) override;

    // needed this for boundary collision
    void checkCollisions(FloatRect leftPaddleBounds, FloatRect rightPaddleBounds, SoundManager& sfx);
    
    FloatRect getGlobalBounds() const;
    float getRadius() const;
};