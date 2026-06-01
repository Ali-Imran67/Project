#include "leaderboard.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Leaderboard::Leaderboard() : backButton("../assets/Textures/LeaderboardFiles/BackButton.png", "../assets/Textures/LeaderboardFiles/BackButtonHover.png", {50.f, 50.f})
{
    count = 0;
}

bool Leaderboard::loadassets(const string& fontpath)
{
    if(!font.openFromFile(fontpath))
    {
        cout << "Failed to load font for leaderboard" << endl;
        fontLoaded = false;
    }
    else
    {
        fontLoaded = true;
    }

    if(!frameTexture.loadFromFile("../assets/Textures/LeaderboardFiles/Frame.png"))
    {
        cout << "Failed to load frame texture for leaderboard" << endl;
    }
    if(!placeholderTexture.loadFromFile("../assets/Textures/LeaderboardFiles/NameWinButton.png"))
    {
        cout << "Failed to load placeholder texture for leaderboard" << endl;
    }
    if(!headertex.loadFromFile("../assets/Textures/LeaderboardFiles/LeaderboardHeader.png"))
    {
        cout << "Failed to load header texture for leaderboard" << endl;
    }
    if(!ranktex.loadFromFile("../assets/Textures/LeaderboardFiles/RankDisplay.png"))
    {
        cout << "Failed to load rank texture for leaderboard" << endl;
    }
    return fontLoaded;
}

void Leaderboard::sortbywins(Playerdata player[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (player[j].score < player[j + 1].score)
            {
                swap(player[j], player[j + 1]);
            }
        }
    }
}

void Leaderboard::update(string p1, string p2, bool p1won, bool p2won)
{
    Playerdata player[100];
    int count = 0;
    ifstream read("leaderboard.txt");
    
    while (read >> player[count].name >> player[count].score)
    {
        count++;
    }
    read.close();
    bool p1found = false;
    for (int i = 0; i < count; i++)
    {
        if (player[i].name == p1)
        {
            if (p1won)
            {
                player[i].score++;
            }
            p1found = true;
            break;
        }
    }
    if (!p1found)
    {
        player[count].name = p1;
        if (p1won)
        {
            player[count].score = 1;
        }
        else
        {
            player[count].score = 0;
        }
        count++;
    }
    bool p2found = false;
    for (int i = 0; i < count; i++)
    {
        if (player[i].name == p2)
        {
            if (p2won)
            {
                player[i].score++;
            }
            p2found = true;
            break;
        }
    }
    if (!p2found)
    {
        player[count].name = p2;
        if (p2won)
        {
            player[count].score = 1;
        }
        else
        {
            player[count].score = 0;
        }
        count++;
    }

    ofstream write("leaderboard.txt");
    if (!write.is_open())
    {
        cout << "Error Encountered: Unable to write data to the File." << endl;
    }
    for (int i = 0; i < count; i++)
    {
        write << setw(10) << player[i].name << setw(20) << player[i].score << endl;
    }
    write.close();
}

void Leaderboard::show(sf::RenderWindow& window, GameState& current_state)
{
    count = 0;
    ifstream read("leaderboard.txt");
    if(read.is_open())
    {
        while (read >> player[count].name >> player[count].score)
        {
            count++;
        }
        read.close();
        sortbywins(player, count);
    }

    bool inleaderboard = true;
    bool leftMousePressed = false;

    while (window.isOpen() && inleaderboard)
    {
        while (const optional event = window.pollEvent())
        {
            if(event->is<Event::Closed>()) window.close();
        }

        bool leftMouseCurrent = Mouse::isButtonPressed(Mouse::Button::Left);
        Vector2i mousePosition = Mouse::getPosition(window);

        backButton.changeTexture(mousePosition);

        if (leftMouseCurrent && !leftMousePressed)
        {
            if (backButton.isClicked(mousePosition))
            {
                inleaderboard = false;
                current_state = GameState::MainMenu;  // Return to the main menu when the back button is clicked
            }
        }
        leftMousePressed = leftMouseCurrent;

        window.clear(sf::Color::Black); //First clear window to Black before drawing the leaderboard
        backButton.create(window); //Creating the back button to return to the menu

        //Drawing Main Frame
        sf::Sprite frameSprite(frameTexture);
        frameSprite.setPosition({(1280.f - frameSprite.getGlobalBounds().size.x) / 2.f, 150.f});
        window.draw(frameSprite);

        //Drawing the Image Header "Leaderboard"
        sf::Sprite headerSprite(headertex);
        headerSprite.setPosition({(1280.f - headerSprite.getGlobalBounds().size.x) / 2.f, 90.f});
        window.draw(headerSprite);

        if (fontLoaded)
        {
           float startX = 250.f;
           float startY = 200.f;

           sf::Text headerRank(font, "Rank", 30);
           headerRank.setPosition({startX, startY});
           window.draw(headerRank);

           sf::Text headerName(font, "Player Name", 30);
           headerName.setPosition({startX + 150.f, startY});
           window.draw(headerName);

           sf::Text headerWins(font, "Wins", 30);
           headerWins.setPosition({startX + 650.f, startY});
           window.draw(headerWins);

           sf::Sprite placeholderSprite(placeholderTexture);
           sf::Sprite rankSprite(ranktex);
           float rowSpacing = 65.f;

           for(int i =0; i < count && i < 5; i++)
           {
                float currentY = startY + 60.f + (i * rowSpacing);

                //Drawing Rank Image Box
                rankSprite.setPosition({startX - 5.f, currentY - 5.f});
                window.draw(rankSprite);

                //Drawing Rank Text Number
                sf::Text rankText(font, to_string(i+1) + ".", 30);
                rankText.setPosition({startX + 10.f, currentY});
                window.draw(rankText);

                //Drawing Player Name Box
                placeholderSprite.setPosition({startX + 140.f, currentY - 5.f});
                window.draw(placeholderSprite);

                //Drawing Player Name Text
                sf::Text nameText(font, player[i].name, 30);
                nameText.setPosition({startX + 150.f, currentY});
                window.draw(nameText);

                //Drawing Player Wins Text
                sf::Text winsText(font, to_string(player[i].score), 30);
                winsText.setPosition({startX + 670.f, currentY});
                window.draw(winsText);
           }
        }

        window.display();
    }

}

