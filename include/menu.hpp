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
    String getPlayer1Name() const { return Player1Name; }
    String getPlayer2Name() const { return Player2Name; }
    void Input(RenderWindow &window, GameState &current_state);
    void draw(RenderWindow &window, GameState &current_state);
    void handleTextEvents(const Event &event, GameState &current_state);
    void updateLeaderboard(const std::string& p1, const std::string& p2, bool p1won, bool p2won);
    void drawLeaderboard(sf::RenderWindow& window, GameState& state);
    void reloadLeaderboardData();
};