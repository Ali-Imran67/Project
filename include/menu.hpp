#pragma once
#include "button.hpp"
#include "audio.hpp"
#include "leaderboard.hpp"
#include "gameState.hpp"

class Menu
{

private:
    button play;
    button leaderboard;

    Texture LogoTexture;
    Sprite LogoSprite;

    SoundManager SFX;

    bool LeftMousePressed = false;

    Leaderboard myleaderboard;

    // ADDING THESE TWO LINES FOR AUDIO DEBOUNCING:
    bool playHoveredLastFrame = false;
    bool leaderboardHoveredLastFrame = false;

public:
    Menu();
    void Input(RenderWindow &window, GameState &current_state);
    void draw(RenderWindow &window);
};