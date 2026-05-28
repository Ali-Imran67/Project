#pragma once
#include "button.hpp"
#include "audio.hpp"
#include "leaderboard.hpp"
#include "gameState.hpp"

class Menu {

    private:

    button play;
    button leaderboard;

    Texture LogoTexture;
    Sprite LogoSprite;

    SoundManager SFX;

    bool LeftMousePressed = false;

    Leaderboard myleaderboard;

    public:

    Menu();
    void Input(RenderWindow& window, GameState& current_state);
    void draw(RenderWindow& window);
};