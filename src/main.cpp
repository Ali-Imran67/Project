#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "audio.hpp"
#include "leaderboard.hpp"
#include "gameState.hpp"
#include "paddle.hpp"
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Ping Pong");
    GameState current_State = GameState::MainMenu;
    Menu mainMenu;

    // Ball Impact Sounds
    SoundManager gameSFX;
    gameSFX.loadSound("Impact", "../assets/Sounds/BallImpact.wav");

    // GamePlay Setup
    float paddleWidth = 20.f;
    float paddleHeight = 100.f;
    float paddleSpeed = 500.f;

    Paddle leftPaddle(Vector2f(50.f, 310.f), Vector2f(0.f, paddleSpeed), paddleWidth, paddleHeight);
    Paddle rightPaddle(Vector2f(1210.f, 310.f), Vector2f(0.f, paddleSpeed), paddleWidth, paddleHeight);

    // Boundaries Setup
    float upperBoundaryY = 20.f;    
    float lowerBoundaryY = 660.f;   
    float boundarythickness = 40.f; 

    sf::RectangleShape upperBoundary(Vector2f(1280.f, boundarythickness));
    upperBoundary.setPosition({0.f, upperBoundaryY});
    upperBoundary.setFillColor(sf::Color(0xc1fbffff)); 

    sf::RectangleShape lowerBoundary(Vector2f(1280.f, boundarythickness));
    lowerBoundary.setPosition({0.f, lowerBoundaryY});
    lowerBoundary.setFillColor(sf::Color(0xc1fbffff)); 

    sf::Font gameFont;
    if (!gameFont.openFromFile("../assets/Orange Kid.otf"))
    {
        printf("Unable to load font for game\n");
    }

    // UI Text Configurations
    sf::Text p1Text(gameFont, "", 40);
    p1Text.setFillColor(sf::Color::Black);
    p1Text.setPosition({50.f, upperBoundaryY - 8.f});

    sf::Text p2Text(gameFont, "", 40);
    p2Text.setFillColor(sf::Color::Black);
    p2Text.setPosition({1150.f, upperBoundaryY - 8.f});

    int p1Score = 0;
    int p2Score = 0;
    sf::Text scoreText(gameFont, "0 : 0", 40);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition({610.f, upperBoundaryY - 8.f});

    bool namesloaded = false;
    sf::Clock clock; 

    // --- MAIN GAME LOOP ---
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); 

        // 1. EVENT POLLING PHASE
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (current_State == GameState::NameEntry)
            {
                mainMenu.handleTextEvents(*event, current_State);
            }
        }

        // 2. REAL-TIME UPDATE PHASE (Grouped cleanly by state)
        switch (current_State)
        {
            case GameState::MainMenu:
                mainMenu.Input(window, current_State);
                break;

            case GameState::Playing:
            {
                // Name Initialization Guard
                if (!namesloaded)
                {
                    p1Text.setString(mainMenu.getPlayer1Name());
                    p2Text.setString(mainMenu.getPlayer2Name());
                    namesloaded = true;
                }

                // Audio Logic Placeholder Check
                bool ballHitsWall = false;
                bool ballHitsPaddle = false;

                if (ballHitsWall || ballHitsPaddle)
                {
                    gameSFX.play("Impact", 100.f);
                }

                // Gameplay Bounds & Input Handling
                float upperLimit = upperBoundaryY + boundarythickness;
                float lowerLimit = lowerBoundaryY; 

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))    leftPaddle.moveUp(deltaTime, upperLimit);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))    leftPaddle.moveDown(deltaTime, lowerLimit);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))   rightPaddle.moveUp(deltaTime, upperLimit);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) rightPaddle.moveDown(deltaTime, lowerLimit);
                
                // TODO: Add collision/ball updates here
                break;
            }
            default:
                break;
        }

        // 3. UNIFIED RENDERING PHASE
        window.clear(sf::Color::Black); 

        switch (current_State)
        {
            case GameState::MainMenu:
            case GameState::NameEntry:
            case GameState::Leaderboard:
                mainMenu.draw(window, current_State);
                break;

            case GameState::Playing:
                window.draw(upperBoundary);
                window.draw(lowerBoundary);
                window.draw(p1Text);
                window.draw(p2Text);
                window.draw(scoreText);
                leftPaddle.draw(window);
                rightPaddle.draw(window);
                // Draw the ball later here
                break;
        }

        window.display();
    }
}