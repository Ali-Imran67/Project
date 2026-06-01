#include "menu.hpp"
#include "leaderboard.hpp"

Menu::Menu() : play("../assets/Textures/PlayButton.png", "../assets/Textures/PlayHover.png", {500.f, 500.f}), leaderboard("../assets/Textures/Leaderboard.png", "../assets/Textures/LeaderboardHover.png", {500.f, 600.f}), LogoSprite(LogoTexture), nameField(menuFont, "../assets/Textures/PlayScreen/NameButton.png", {320.f, 360.f}, 80, 12, "Enter Player 1...")
{

    if (!menuFont.openFromFile("../assets/Orange Kid.otf")) // trying to check if font loaded
    {
        printf("Unable to load font\n");
    }
    if (LogoTexture.loadFromFile("../assets/Textures/Logo.png"))
    {
        LogoSprite.setTexture(LogoTexture, true);
        float xPos = (1280.0f / 2.0f) - (LogoSprite.getGlobalBounds().size.x / 2.0f);
        LogoSprite.setPosition({xPos, 240.0f});
    }

    SFX.loadSound("MenuTheme", "../assets/Sounds/MenuMusic.mp3");
    SFX.setLoop("MenuTheme", true);
    SFX.play("MenuTheme", 50.f);

    myleaderboard.loadassets("../assets/Orange Kid.otf");

    //  Adding this line for Button Hover sound
    SFX.loadSound("HoverSound", "../assets/Sounds/ButtonHover.wav");
    nameField.setSelected(false);
}

void Menu::Input(RenderWindow &window, GameState &current_state)
{
    // 1.We moved this to the top (So both hover and click can use it)
    Vector2i mousePosition = Mouse::getPosition(window);

    // --- HOVER AUDIO DETECTION ---
    // Check if mouse is within the boundaries of the Play or Leaderboard buttons
    bool currentlyOverPlay = (mousePosition.x >= 500.f && mousePosition.x <= 780.f && mousePosition.y >= 500.f && mousePosition.y <= 580.f);
    bool currentlyOverLeaderboard = (mousePosition.x >= 500.f && mousePosition.x <= 780.f && mousePosition.y >= 600.f && mousePosition.y <= 680.f);

    // Play the sound only at the exact split-second the cursor crosses onto the button area
    if ((currentlyOverPlay && !playHoveredLastFrame) || (currentlyOverLeaderboard && !leaderboardHoveredLastFrame))
    {
        SFX.play("HoverSound", 100.f);
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

            current_state = GameState::NameEntry;
            nameField.setSelected(true);

            if (SFX.IsPlaying("MenuTheme"))
            {
                SFX.stop("MenuTheme");
            }
        }
        if (leaderboard.isClicked(mousePosition))
        {
            // display leaderboard
            current_state = GameState::Leaderboard;
        }
    }
    LeftMousePressed = LeftMouseCurrent;
}

void Menu::handleTextEvents(const Event &event, GameState &current_state)
{

    nameField.handleInput(event);

    // Check if the user pressed the Enter/Return key
    if (const auto *keyPressed = event.getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::Enter)
        {

            String enteredText = nameField.getText();
            if (enteredText.isEmpty())
            {
                return; // you won't be able to submit an empty name
            }

            if (inputStage == 1)
            {
                // save Player 1 name
                Player1Name = enteredText;
                cout << "Player 1 Saved: " << Player1Name.toAnsiString() << endl;

                inputStage = 2;

                // reset the input box for the next player
                nameField.clear();
                nameField.setPlaceholder("Enter Player 2...");
            }
            else if (inputStage == 2)
            {
                Player2Name = enteredText;
                cout << "Player 2 Saved: " << Player2Name.toAnsiString() << endl;

                current_state = GameState::Playing; // setting state after acquiring both names

                inputStage = 1;
                nameField.clear();
                nameField.setPlaceholder("Enter Player 1...");
            }
        }
    }
}

void Menu::draw(RenderWindow &window, GameState &current_state) // creating the buttons finally
{
    if (current_state == GameState::MainMenu)
    {
        window.draw(LogoSprite);
        play.create(window);
        leaderboard.create(window);

        Vector2i mousePosition = Mouse::getPosition(window); // running the hover functions
        play.changeTexture(mousePosition);
        leaderboard.changeTexture(mousePosition);
    }

    else if (current_state == GameState::NameEntry)
    {
        window.draw(LogoSprite);
        nameField.draw(window);
    }

    else if (current_state == GameState::Leaderboard)
    {
        myleaderboard.show(window, current_state);
    }
}