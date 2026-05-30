#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "leaderboard.hpp"
#include "gameState.hpp"
#include "paddle.hpp"

int main()
{
    RenderWindow window(VideoMode({1280, 720}), "Ping Pong");
    GameState current_State = GameState::MainMenu;
    Menu mainMenu;

    // GamePlay Setup
    float paddleWidth = 20.f;
    float paddleHeight = 100.f;
    float paddleSpeed = 500.f;

    //Left Paddle
    Paddle leftPaddle(Vector2f(50.f, 310.f), Vector2f(0.f, paddleSpeed), paddleWidth, paddleHeight);

    //Right Paddle
    Paddle rightPaddle(Vector2f(1210.f, 310.f), Vector2f(0.f, paddleSpeed), paddleWidth, paddleHeight);

    // Boundaries (Upper and Lower)
    sf::RectangleShape upperBoundary(Vector2f(1280.f, 10.f));
    upperBoundary.setPosition({0.f, 0.f});
    upperBoundary.setFillColor(sf::Color::White);

    sf::RectangleShape lowerBoundary(Vector2f(1280.f, 10.f));
    lowerBoundary.setPosition({0.f, 710.f});
    lowerBoundary.setFillColor(sf::Color::White);

    sf::Clock clock; // Clock for delta time calculation

    while (window.isOpen())
    {

        float deltaTime = clock.restart().asSeconds(); // Calculate delta time

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


        // GamePlay Logic
        if(current_State == GameState::Playing)
        {
            //Left Paddle Input keys
            if (Keyboard::isKeyPressed(Keyboard::Key::W))
            {
                leftPaddle.moveUp(deltaTime);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::S))
            {
                leftPaddle.moveDown(deltaTime, 720.f);
            }

            //Right Paddle Input keys
            if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            {
                rightPaddle.moveUp(deltaTime);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Down))
            {
                rightPaddle.moveDown(deltaTime, 720.f);
            }

            // Add collision detection and ball movement logic here
        }


        window.clear(sf::Color::Black);    // Clear the window with black color before drawing

        // Drawing logic based on game state
        if (current_State == GameState::MainMenu || current_State == GameState::NameEntry || current_State == GameState::Leaderboard)
        {
            mainMenu.draw(window, current_State);
        }
        else if(current_State == GameState::Playing)
        {
            window.draw(upperBoundary);
            window.draw(lowerBoundary);
            leftPaddle.draw(window);
            rightPaddle.draw(window);

            // Draw the ball Later here.
        }
        
        
        window.display();
    }
}