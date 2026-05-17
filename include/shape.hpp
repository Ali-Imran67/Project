#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class shape {
    protected:

    Vector2f position;
    Vector2f speed;

    public:

    shape(Vector2f initialPos, Vector2f initialSpeed) : position(initialPos), speed(initialSpeed) {}

    virtual ~shape() = default;
    virtual void draw(RenderWindow& window) = 0;
    
    virtual void update(float deltaTime)
    {
        position +=  speed * deltaTime;
    }

    Vector2f getPosition() const
    {
        return position;
    }
    void setPosition(Vector2f pos)
    {
        position = pos;
    }

    Vector2f getSpeed() const 
    {
        return speed;
    }
    void setSpeed(Vector2f sp)
    {
        speed = sp;
    }
};