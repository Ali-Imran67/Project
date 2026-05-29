#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "leaderboard.hpp"

int main()
{
    RenderWindow window(VideoMode({1280, 720}), "Ping Pong");
    GameState current_State = GameState::MainMenu;
    Menu mainMenu;

    while (window.isOpen())
    {

        while (const auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            if (current_State == GameState::NameEntry)
            {
                mainMenu.handleTextEvents(*event, current_State);
            }
        }

        if (current_State == GameState::MainMenu) 
        { 
            mainMenu.Input(window, current_State);
        }

        window.clear();

        // check our screens sequentially 
        if (current_State == GameState::MainMenu) 
        {
            mainMenu.draw(window, current_State);
        }
        else if (current_State == GameState::NameEntry) 
        {
            mainMenu.draw(window, current_State); 
        }
        else if (current_State == GameState::Leaderboard) 
        { 
            mainMenu.draw(window, current_State);
        }
        
        window.display();
    }
}