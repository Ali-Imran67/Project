#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class shape {
    protected:

    Vector2f position;
    Vector2f speed;

    public:

    shape(Vector2f initialPos, Vector2f initialSpeed) : position(initialPos), speed(initialSpeed) {} // constructor

    virtual ~shape() = default; // automatically frees memory thats why I used default
    virtual void draw(RenderWindow& window) = 0; // 0 implies that each derived class will have to create its own draw function logic
    
    virtual void update(float deltaTime); // make a function for updating position with time

    Vector2f getPosition() const; // should return position
    void setPosition(Vector2f pos); // used to set position

    Vector2f getSpeed() const;
    void setSpeed(Vector2f sp);
};