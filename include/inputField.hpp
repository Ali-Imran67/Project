#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"

using namespace std;
using namespace sf;

class InputBox {
    private:
    Font& var_Font;
    Text text_var;
    String var_inputString;
    String var_placeHolder;
    bool var_isSelected;
    int textLimit;

    button BoxFrame;

    static Font loadHelper(const string& path);
    void updateDisplay();

    public:

    //InputBox() : text_var(var_Font),textLimit(0), var_isSelected(false) {};
    InputBox(Font& sharedFont, string TextPath, Vector2f position, unsigned int size, unsigned int Limit, String place_Holder = "");

    void handleInput(const Event& event);
    void draw(RenderWindow& window);

    String getText() const {
        return var_inputString;
    }
    void clear();

    void setPlaceholder(String newPlaceHolder);

    void setSelected(bool Selected);
    bool isSelected() const {
        return var_isSelected;
    }
};