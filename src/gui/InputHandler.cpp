#include "InputHandler.h"

InputHandler::InputHandler() {}

InputCommand InputHandler::processKeyboardState() {
    InputCommand cmd = {0, 0, false};
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        cmd.dy = 1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        cmd.dy = -1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        cmd.dx = -1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        cmd.dx = 1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        cmd.dx = -1;
        cmd.dy = 1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        cmd.dx = 1;
        cmd.dy = 1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        cmd.dx = -1;
        cmd.dy = -1;
        cmd.valid = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        cmd.dx = 1;
        cmd.dy = -1;
        cmd.valid = true;
    }
    
    return cmd;
}
