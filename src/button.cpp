
#include "button.hpp"


button::button(string normalPath, string hoverPath, Vector2f position) : sprite(texture) // constructor, loading and setting stuff
{
    
    if (!texture.loadFromFile(normalPath))
    {
        printf("couldnt load normal\n");
    }

    if (!hover.loadFromFile(hoverPath))
    {
        printf("couldn't load hover\n");
    }

    sprite.setTexture(texture, true);
    sprite.setPosition(position);
}

void button::changeTexture(Vector2i mousePosition) // for hover buttons
{
    if (sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)))
    {
        sprite.setTexture(hover, true);
    }
    else
    {
        sprite.setTexture(texture, true);
    }
}

void button::create(RenderWindow& window)
{
    //printf("drawing button at %f, %f\n", sprite.getPosition().x, sprite.getPosition().y);
    window.draw(sprite);

}

bool button::isClicked(Vector2i mousePosition)
{
    return Mouse::isButtonPressed(Mouse::Button::Left) && sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition));
}