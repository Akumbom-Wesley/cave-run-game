#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(sf::RenderWindow* window, sf::Font* font,
                               int windowWidth, int windowHeight, Game* game)
    : window(window), font(font), windowWidth(windowWidth), 
      windowHeight(windowHeight), game(game) {}

GameOverScreen::~GameOverScreen() {}

void GameOverScreen::show() {
    // Brief pause to see final state
    sf::sleep(sf::seconds(1));
    
    // Show until user closes
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape || 
                    event.key.code == sf::Keyboard::Enter) {
                    window->close();
                    return;
                }
            }
        }
        
        window->clear(sf::Color::Black);
        
        bool playerWon = game->hasPlayerWon();
        drawTitle(playerWon);
        drawMessage(playerWon, game->getDeathCause());
        drawStats(game->getPlayer()->getHealth(), game->getTurnCount());
        drawExitInstruction();
        
        window->display();
    }
}

void GameOverScreen::drawTitle(bool playerWon) {
    sf::Text titleText;
    titleText.setFont(*font);
    titleText.setCharacterSize(50);
    
    if (playerWon) {
        titleText.setString("YOU WIN!");
        titleText.setFillColor(sf::Color::Green);
    } else {
        titleText.setString("GAME OVER!");
        titleText.setFillColor(sf::Color::Red);
    }
    
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setPosition(windowWidth / 2.f - bounds.width / 2.f, 
                         windowHeight / 2.f - 150.f);
    window->draw(titleText);
}

void GameOverScreen::drawMessage(bool playerWon, DeathCause cause) {
    sf::Text messageText;
    messageText.setFont(*font);
    messageText.setCharacterSize(25);
    messageText.setFillColor(sf::Color(200, 200, 200));
    
    if (playerWon) {
        messageText.setString("You escaped the cave!");
    } else {
        if (cause == MONSTER_CAUGHT) {
            messageText.setString("You were caught by the monster!");
        } else if (cause == HEALTH_DEPLETED) {
            messageText.setString("You collapsed from your injuries!");
        } else {
            messageText.setString("Better luck next time!");
        }
    }
    
    sf::FloatRect bounds = messageText.getLocalBounds();
    messageText.setPosition(windowWidth / 2.f - bounds.width / 2.f, 
                           windowHeight / 2.f - 80.f);
    window->draw(messageText);
}

void GameOverScreen::drawStats(int health, int turns) {
    sf::Text statsText;
    statsText.setFont(*font);
    statsText.setCharacterSize(30);
    statsText.setFillColor(sf::Color::Yellow);
    statsText.setString("Final HP: " + std::to_string(health) + 
                       "\nTurns: " + std::to_string(turns));
    
    sf::FloatRect bounds = statsText.getLocalBounds();
    statsText.setPosition(windowWidth / 2.f - bounds.width / 2.f, 
                         windowHeight / 2.f);
    window->draw(statsText);
}

void GameOverScreen::drawExitInstruction() {
    sf::Text exitText;
    exitText.setFont(*font);
    exitText.setCharacterSize(20);
    exitText.setFillColor(sf::Color(150, 150, 150));
    exitText.setString("Press ENTER or ESC to exit");
    
    sf::FloatRect bounds = exitText.getLocalBounds();
    exitText.setPosition(windowWidth / 2.f - bounds.width / 2.f, 
                        windowHeight - 100.f);
    window->draw(exitText);
}
