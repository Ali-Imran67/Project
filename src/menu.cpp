#include "menu.hpp"
#include "Leaderboard.hpp"

Menu::Menu() : play("../assets/Textures/PlayButton.png", "../assets/Textures/PlayHover.png", {500.f, 500.f}), leaderboard("../assets/Textures/Leaderboard.png", "../assets/Textures/LeaderboardHover.png", {500.f, 600.f}), LogoSprite(LogoTexture)
{

    if (LogoTexture.loadFromFile("../assets/Textures/Logo.png"))
    {
        LogoSprite.setTexture(LogoTexture, true);
        float xPos = (1280.0f / 2.0f) - (LogoSprite.getGlobalBounds().size.x / 2.0f);
        LogoSprite.setPosition({xPos, 240.0f});
    }

    SFX.loadSound("MenuTheme", "../assets/Sounds/MenuTheme.wav");
    SFX.setLoop("MenuTheme", true);
    SFX.play("MenuTheme");

    myleaderboard.loadassets("../assets/Orange Kid.otf");

    // ADDING THIS LINE FOR BUTTON HOVER SOUND
    SFX.loadSound("HoverSound", "../assets/Sounds/ButtonHover.wav");
}

void Menu::Input(RenderWindow &window, GameState &current_state)
{
    // 1. WE MOVED THIS TO THE TOP (So both hover and click can use it)
    Vector2i mousePosition = Mouse::getPosition(window);

    // --- HOVER AUDIO DETECTION ---
    // Check if mouse is within the boundaries of the Play or Leaderboard buttons
    bool currentlyOverPlay = (mousePosition.x >= 500.f && mousePosition.x <= 780.f && mousePosition.y >= 500.f && mousePosition.y <= 580.f);
    bool currentlyOverLeaderboard = (mousePosition.x >= 500.f && mousePosition.x <= 780.f && mousePosition.y >= 600.f && mousePosition.y <= 680.f);

    // Play the sound ONLY at the exact split-second the cursor crosses onto the button area
    if ((currentlyOverPlay && !playHoveredLastFrame) || (currentlyOverLeaderboard && !leaderboardHoveredLastFrame))
    {
        SFX.play("HoverSound");
    }

    // Save current frame statuses for the next frame
    playHoveredLastFrame = currentlyOverPlay;
    leaderboardHoveredLastFrame = currentlyOverLeaderboard;

    bool LeftMouseCurrent = Mouse::isButtonPressed(Mouse::Button::Left);

    if (LeftMouseCurrent && !LeftMousePressed)
    {

        if (play.isClicked(mousePosition)) // TO DO: add a debounce to this
        {
            printf("Play button clicked!\n");

            if (SFX.IsPlaying("MenuTheme"))
            {
                SFX.stop("MenuTheme");
            }
        }
        if (leaderboard.isClicked(mousePosition))
        {
            // display leaderboard
            myleaderboard.show(window);
        }
    }
    LeftMousePressed = LeftMouseCurrent;
}

void Menu::draw(RenderWindow &window) // creating the buttons finally
{
    window.draw(LogoSprite);
    play.create(window);
    leaderboard.create(window);

    Vector2i mousePosition = Mouse::getPosition(window); // running the hover functions
    play.changeTexture(mousePosition);
    leaderboard.changeTexture(mousePosition);
}