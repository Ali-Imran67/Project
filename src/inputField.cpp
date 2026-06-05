#include "inputField.hpp"

Font InputBox::loadHelper(const std::string& path) {
    sf::Font font;
    if (!font.openFromFile(path)) {
        printf("Failed to open font.");
    }
    return font;
}

InputBox::InputBox(Font& sharedFont, string FrameTexturePath, Vector2f position, unsigned int size, unsigned int limit, String placeholder)
    : var_Font(sharedFont), BoxFrame(FrameTexturePath, FrameTexturePath, position), text_var(var_Font), textLimit(limit), var_isSelected(false), var_placeHolder(placeholder) 
{

    if (!var_Font.openFromFile("../assets/Orange Kid.otf")) {
        printf("Couldn't load font\n");
    }
    // initializes text variable
    text_var.setCharacterSize(size);
    text_var.setPosition(position + Vector2f(15.f,10.f));
    
    updateDisplay();
}

void InputBox::updateDisplay() {
    // if the string is empty, it should display the placeholder
    if (var_inputString.isEmpty()) {
        text_var.setString(var_placeHolder);
        
        // make it gray if unselected, white if selected and active
        if (!var_isSelected) {
            text_var.setFillColor(Color(120, 120, 120)); 
        } else {
            text_var.setFillColor(Color(180, 180, 180));
        }
    } 
    else {
        // typed out text
        text_var.setString(var_inputString);
        text_var.setFillColor(Color::White); 
    }
}

// toggles selection state 
void InputBox::setSelected(bool selected) {
    var_isSelected = selected;
    updateDisplay();
}

// wipes the current input string clean
void InputBox::clear() {
    var_inputString.clear();
    updateDisplay();
}
void InputBox::setPlaceholder(String newPlaceholder) {
    var_placeHolder = newPlaceholder;
    updateDisplay();
}


void InputBox::handleInput(const Event& event) { 

    if (!var_isSelected) return;

    // checking if the event is specifically a TextEntered event
    if (const auto* textEntered = event.getIf<Event::TextEntered>()) {
        
        char32_t unicodeValue = textEntered->unicode;

        // backspace functionality
        if (unicodeValue == 8) {
            if (!var_inputString.isEmpty()) {
                var_inputString.erase(var_inputString.getSize() - 1, 1);
            }
        }
        // handling normal typing here
        else if (var_inputString.getSize() < textLimit) {
            if ((unicodeValue >= 'A' && unicodeValue <= 'Z') ||
                (unicodeValue >= 'a' && unicodeValue <= 'z') ||
                (unicodeValue >= '0' && unicodeValue <= '9')) 
            {
                // will only write uppercase letters
                if (unicodeValue >= 'a' && unicodeValue <= 'z') {
                    unicodeValue -= 32; // 'a'(97) - 'A'(65) = 32
                }
                var_inputString += unicodeValue;
            }
        }
        
        updateDisplay();
    }
}


void InputBox::draw(RenderWindow& window) {
    BoxFrame.create(window); // create input box
    window.draw(text_var);
}

