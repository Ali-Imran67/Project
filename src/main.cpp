#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "leaderboard.hpp"
#include "gameState.hpp"
#include "paddle.hpp"
#include <string>

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
    float upperBoundaryY = 20.f; // Y position of the upper boundary
    float lowerBoundaryY = 660.f; // Y position of the lower boundary
    float boundarythickness = 40.f; // Thickness of the boundary rectangles

    sf::RectangleShape upperBoundary(Vector2f(1280.f, boundarythickness));
    upperBoundary.setPosition({0.f, upperBoundaryY});
    upperBoundary.setFillColor(sf::Color(0xc1fbffff));  //light blue color of boundary as decided 

    sf::RectangleShape lowerBoundary(Vector2f(1280.f, boundarythickness));
    lowerBoundary.setPosition({0.f, lowerBoundaryY});
    lowerBoundary.setFillColor(sf::Color(0xc1fbffff));  //light blue color of boundary as decided 

    sf::Font gameFont;
    if (!gameFont.openFromFile("../assets/Orange Kid.otf"))
    {
        printf("Unable to load font for game\n");
    }

    sf::Text p1Text(gameFont, "", 40);
    p1Text.setFillColor(sf::Color::Black);
    p1Text.setPosition({50.f, upperBoundaryY + 2.f});

    sf::Text p2Text(gameFont, "", 40);
    p2Text.setFillColor(sf::Color::Black);
    p2Text.setPosition({1150.f, upperBoundaryY + 2.f});

    //Score Text
    int p1Score = 0;
    int p2Score = 0;
    sf::Text scoreText(gameFont, "0 : 0", 40);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition({610.f, upperBoundaryY + 2.f});

    bool namesloaded = false;

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
            if (!namesloaded)
            {
                p1Text.setString(mainMenu.getPlayer1Name());
                p2Text.setString(mainMenu.getPlayer2Name());
                namesloaded = true;
            }

            float upperLimit = upperBoundaryY + boundarythickness;
            float lowerLimit = lowerBoundaryY; // Calculation of boundaries so Paddles don't go out 

            //Left Paddle Input keys
            if (Keyboard::isKeyPressed(Keyboard::Key::W))
            {
                leftPaddle.moveUp(deltaTime, upperLimit);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::S))
            {
                leftPaddle.moveDown(deltaTime, lowerLimit);
            }

            //Right Paddle Input keys
            if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            {
                rightPaddle.moveUp(deltaTime, upperLimit);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Down))
            {
                rightPaddle.moveDown(deltaTime, lowerLimit);
            }

            // TODO: Add collision detection and ball movement logic here
            // Update the scoreText string when points are scored:
            // scoreText.setString(std::to_string(p1ScoreCounter) + "  :  " + std::to_string(p2ScoreCounter));
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
            window.draw(p1Text);
            window.draw(p2Text);
            window.draw(scoreText);
            leftPaddle.draw(window);
            rightPaddle.draw(window);

            // Draw the ball Later here.
        }
        
        
        window.display();
    }
}