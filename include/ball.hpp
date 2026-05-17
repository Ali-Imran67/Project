#pragma once
#include "shape.hpp"

class Ball: public shape {

    private:
    CircleShape circle;

    public:
    Ball(Vector2f initialPos, float radius, Vector2f initialSpeed);

    void draw(RenderWindow& window) override;

};