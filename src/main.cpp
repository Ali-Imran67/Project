#include <SFML/Graphics.hpp>
#include "menu.hpp"
// new change
int main()
{
    RenderWindow window(
        VideoMode({1280, 720}),
        "Ping Pong");
    Menu mainMenu;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        mainMenu.Input(window);

        window.clear();
        mainMenu.draw(window);
        window.display();
        // testing
    }
}