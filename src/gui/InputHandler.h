#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

struct InputCommand {
    int dx;
    int dy;
    bool valid;
};

class InputHandler {
public:
    InputHandler();
    InputCommand processInput(const sf::Event& event);
    InputCommand processKeyboardState();
};

#endif
