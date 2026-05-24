#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iomanip>
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
        bool fontLoaded;
        void sortbywins(Playerdata player[], int count);

    public:
        
        Leaderboard(){};
        
        bool loadFont(const string& fontpath);
        void update(string p1, string p2, bool p1won, bool p2won);
        void displayLeaderboard( sf::RenderWindow& window);
        
};
#endif
