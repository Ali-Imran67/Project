#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class button {

    private:

    Texture texture; // image that it shows
    Texture hover; // changed image when u hover ur mouse
    Sprite sprite;

    public:

    button(string normalPath, string hoverPath, Vector2f position);

    void changeTexture(Vector2i mousePosition);
    void create(RenderWindow& window); // the current window in which we're playing ping pong
    bool isClicked(Vector2i mousePosition);

};