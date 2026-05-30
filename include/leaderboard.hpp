#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "gameState.hpp"
#include <fstream>
#include <string>
#include "button.hpp"

using namespace std;

struct Playerdata
{
    string name;
    int score;
};

class Leaderboard
{
    private:
        
        Playerdata player[100];
        int count = 0;

        sf::Font font;
        sf::Texture headertex;    //for the Leaderboard header
        sf::Texture ranktex;     //for the rank display (1st, 2nd, 3rd)
        sf::Texture frameTexture;   //for the bg
        sf::Texture placeholderTexture;   //for the player

        button backButton;  //back button to return to the main menu

        bool fontLoaded;
        void sortbywins(Playerdata player[], int count);

    public:
        
        Leaderboard();
        
        bool loadassets(const string& fontpath);
        void update(string p1, string p2, bool p1won, bool p2won);
        void show(sf::RenderWindow& window, GameState& current_state);
        
};
#endif
