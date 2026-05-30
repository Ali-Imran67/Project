#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "audio.hpp"

int main()
{
    RenderWindow window(VideoMode({1280, 720}), "Ping Pong");
    GameState current_State = GameState::MainMenu;
    Menu mainMenu;

    // ADDING THESE  LINES FOR BALL IMPACT:
    SoundManager gameSFX;
    gameSFX.loadSound("Impact", "../assets/Sounds/BallImpact.wav");

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent()) // close game
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        if (current_State == GameState::MainMenu)
        { // handling button presses
          // mainMenu.Input(window, current_State);
        }

        // --- UPDATED CODE FOR BALL IMPACT SFX  ---
        else if (current_State == GameState::Playing)
        {
            // Temporary placeholder variables so the compiler doesn't give an error.
            // We can Change these to your actual ball/paddle collision conditions later!
            bool ballHitsWall = false;
            bool ballHitsPaddle = false;

            // Trigger when the ball collides with top or bottom screen boundaries
            if (ballHitsWall)
            {
                gameSFX.play("Impact");
            }

            // Trigger when the ball collides with player or enemy paddles
            if (ballHitsPaddle)
            {
                gameSFX.play("Impact");
            }
        }

        window.clear();

        if (current_State == GameState::MainMenu) // displaying info on screen
        {
            mainMenu.draw(window, current_State);
        }
        else if (current_State == GameState::Leaderboard)
        {
            // TO DO: Kabeer this is where the leaderboard goes
        }
        window.display();
    }
}
