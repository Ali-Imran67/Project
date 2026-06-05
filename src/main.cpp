#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "audio.hpp"
#include "leaderboard.hpp"
#include "gameState.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Ping Pong");
    GameState current_State = GameState::MainMenu;
    Menu mainMenu;

    // Ball Impact Sounds
    SoundManager gameSFX;
    gameSFX.loadSound("Impact", "../assets/Sounds/BallImpact.mp3");

    // GamePlay Setup
    float paddleWidth = 20.f;
    float paddleHeight = 100.f;
    float paddleSpeed = 500.f;

    Paddle leftPaddle(Vector2f(50.f, 310.f), Vector2f(0.f, paddleSpeed), paddleWidth, paddleHeight);
    Paddle rightPaddle(Vector2f(1210.f, 310.f), Vector2f(0.f, paddleSpeed), paddleWidth, paddleHeight);

    // Ball Initialization
    Ball gameBall(Vector2f(640.f, 360.f), 12.f, Vector2f(400.f, 300.f));

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

    sf::Text pauseText(gameFont, "GAME PAUSED - PRESS 'P' TO RESUME", 30);
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setPosition({450.f, lowerBoundaryY + 2.f}); 

    // Game Over UI Text elements
    sf::Text winText(gameFont, "", 60);
    winText.setFillColor(sf::Color::Yellow);

    sf::Text gameOverOptions(gameFont, "PRESS 'R' FOR REMATCH  |  PRESS 'M' FOR MAIN MENU", 35);
    gameOverOptions.setFillColor(sf::Color::White);
    
    // Perfect pixel bounding box alignment for the options subtext
    sf::FloatRect optionsRect = gameOverOptions.getLocalBounds();
    gameOverOptions.setOrigin({
        optionsRect.position.x + (optionsRect.size.x / 2.f),
        optionsRect.position.y + (optionsRect.size.y / 2.f)
    });
    gameOverOptions.setPosition({640.f, 440.f});

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

            // Real-Time Keyboard Toggle Listeners via PollEvent
            if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                // Pause/Resume Input Toggle
                if (keyPressed->code == sf::Keyboard::Key::P)
                {
                    if (current_State == GameState::Playing)       current_State = GameState::Paused;
                    else if (current_State == GameState::Paused)  current_State = GameState::Playing;
                }

                // GameOver Navigation Input Switches
                if (current_State == GameState::GameOver)
                {
                    // Rematch selection option
                    if (keyPressed->code == sf::Keyboard::Key::R)
                    {
                        p1Score = 0;
                        p2Score = 0;
                        scoreText.setString("0 : 0");
                        gameBall.setPosition({640.f, 360.f});
                        gameBall.setSpeed({400.f, 300.f});
                        leftPaddle.setPosition({50.f, 310.f});
                        rightPaddle.setPosition({1210.f, 310.f});
                        current_State = GameState::Playing;
                    }
                    // Return to Menu selection option
                    if (keyPressed->code == sf::Keyboard::Key::M)
                    {
                        p1Score = 0;
                        p2Score = 0;
                        scoreText.setString("0 : 0");
                        namesloaded = false; // Force re-pull name strings on future matches
                        
                        // Reset the ball here so it doesn't trigger a score on frame 1 of the next game
                        gameBall.setPosition({640.f, 360.f});
                        gameBall.setSpeed({400.f, 300.f});
                        leftPaddle.setPosition({50.f, 310.f});
                        rightPaddle.setPosition({1210.f, 310.f});
                        
                        current_State = GameState::MainMenu;
                    }
                }
            }
        }

        // 2. REAL-TIME UPDATE PHASE
        switch (current_State)
        {
            case GameState::MainMenu:
                mainMenu.Input(window, current_State);
                break;

            case GameState::Playing:
            {
                if (!namesloaded)
                {
                    p1Text.setString(mainMenu.getPlayer1Name());
                    p2Text.setString(mainMenu.getPlayer2Name());
                    namesloaded = true;
                }

                float upperLimit = upperBoundaryY + boundarythickness;
                float lowerLimit = lowerBoundaryY; 

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))    leftPaddle.moveUp(deltaTime, upperLimit);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))    leftPaddle.moveDown(deltaTime, lowerLimit);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))   rightPaddle.moveUp(deltaTime, upperLimit);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) rightPaddle.moveDown(deltaTime, lowerLimit);
                
                gameBall.update(deltaTime);
                gameBall.checkCollisions(leftPaddle.getBounds(), rightPaddle.getBounds(), gameSFX);

                // Scoring Metrics Processing
                if (gameBall.getPosition().x < 0.f) // Right player scores
                {
                    p2Score++;
                    scoreText.setString(std::to_string(p1Score) + " : " + std::to_string(p2Score));
                    
                    if (p2Score >= 5)
                    {
                        std::string p1Name = mainMenu.getPlayer1Name().toAnsiString();
                        std::string p2Name = mainMenu.getPlayer2Name().toAnsiString();

                        // Fire automatic file storage update (P2 Won, P1 Lost)
                        mainMenu.updateLeaderboard(p1Name, p2Name, false, true);

                        std::string winStr = p2Name + " WINS THE MATCH!";
                        winText.setString(winStr);
                        
                        // Pixel perfect character box centering alignment calculation
                        sf::FloatRect textRect = winText.getLocalBounds();
                        winText.setOrigin({textRect.position.x + (textRect.size.x / 2.f), textRect.position.y + (textRect.size.y / 2.f)});
                        winText.setPosition({640.f, 360.f});
                        
                        current_State = GameState::GameOver;
                    }
                    else
                    {
                        gameBall.setPosition({640.f, 360.f});
                        gameBall.setSpeed({400.f, -300.f});
                    }
                }
                else if (gameBall.getPosition().x > 1280.f) // Left player scores
                {
                    p1Score++;
                    scoreText.setString(std::to_string(p1Score) + " : " + std::to_string(p2Score));

                    if (p1Score >= 5)
                    {
                        std::string p1Name = mainMenu.getPlayer1Name().toAnsiString();
                        std::string p2Name = mainMenu.getPlayer2Name().toAnsiString();

                        // Fire automatic file storage update (P1 Won, P2 Lost)
                        mainMenu.updateLeaderboard(p1Name, p2Name, true, false);

                        std::string winStr = p1Name + " WINS THE MATCH!";
                        winText.setString(winStr);
                        
                        // Pixel perfect character box centering alignment calculation
                        sf::FloatRect textRect = winText.getLocalBounds();
                        winText.setOrigin({textRect.position.x + (textRect.size.x / 2.f), textRect.position.y + (textRect.size.y / 2.f)});
                        winText.setPosition({640.f, 360.f});
                        
                        current_State = GameState::GameOver;
                    }
                    else
                    {
                        gameBall.setPosition({640.f, 360.f});
                        gameBall.setSpeed({-400.f, 300.f});
                    }
                }
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
                mainMenu.draw(window, current_State);
                break;

            case GameState::Leaderboard:
                mainMenu.drawLeaderboard(window, current_State);
                break;
            case GameState::Playing:
            case GameState::Paused:
            case GameState::GameOver: 
                window.draw(upperBoundary);
                window.draw(lowerBoundary);
                window.draw(p1Text);
                window.draw(p2Text);
                window.draw(scoreText);
                leftPaddle.draw(window);
                rightPaddle.draw(window);
                
                if (current_State != GameState::GameOver) 
                {
                    gameBall.draw(window); 
                }

                if (current_State == GameState::Paused)
                {
                    window.draw(pauseText);
                }
                else if (current_State == GameState::GameOver)
                {
                    window.draw(winText);
                    window.draw(gameOverOptions);
                }
                break;
        }

        window.display();
    }
}