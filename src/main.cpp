#include <SFML/Graphics.hpp>
#include "menu.hpp"

int main()
{
    RenderWindow window(VideoMode({1280, 720}),"Ping Pong");
    GameState current_State = GameState::MainMenu;
    Menu mainMenu;


    while (window.isOpen())
    {
        while (const optional event = window.pollEvent()) // close game
        {
            if (event->is<Event::Closed>())
                window.close();
        }


        if (current_State == GameState::MainMenu) { // handling button presses
            mainMenu.Input(window, current_State);
            
        }
        window.clear();

        if (current_State == GameState::MainMenu) // displaying info on screen
        {
            mainMenu.draw(window);
        }
        else if (current_State == GameState::Leaderboard) {
            // TO DO: Kabeer this is where the leaderboard goes
        }
        window.display();
        
    }
}
