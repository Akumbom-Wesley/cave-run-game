#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class GameOverScreen {
private:
    sf::RenderWindow* window;
    sf::Font* font;
    int windowWidth;
    int windowHeight;
    Game* game;
    
    void drawTitle(bool playerWon);
    void drawMessage(bool playerWon, DeathCause cause);
    void drawStats(int health, int turns);
    void drawExitInstruction();
    
public:
    GameOverScreen(sf::RenderWindow* window, sf::Font* font, 
                   int windowWidth, int windowHeight, Game* game);
    ~GameOverScreen();
    
    void show();  // Main method to display game over screen
};

#endif
