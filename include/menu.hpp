#pragma once
#include "button.hpp"
#include "audio.hpp"
#include "leaderboard.hpp"
#include "inputField.hpp"
#include "gameState.hpp"

class Menu
{

private:
    button play;
    button leaderboard;

    Texture LogoTexture;
    Sprite LogoSprite;

    String Player1Name, Player2Name;
    int inputStage = 1;

    SoundManager SFX;

    bool LeftMousePressed = false;

    Leaderboard myleaderboard;
    Font menuFont;
    InputBox nameField;

    // ADDING THESE TWO LINES FOR AUDIO DEBOUNCING:
    bool playHoveredLastFrame = false;
    bool leaderboardHoveredLastFrame = false;

public:
    Menu();
    void Input(RenderWindow &window, GameState &current_state);
    void draw(RenderWindow &window, GameState &current_state);
    void handleTextEvents(const Event &event, GameState &current_state);
};