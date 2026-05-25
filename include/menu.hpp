#pragma once
#include "button.hpp"
#include "audio.hpp"

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
    void Input(RenderWindow& window);
    void draw(RenderWindow& window);
};