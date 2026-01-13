#include "UIRenderer.h"

UIRenderer::UIRenderer(sf::RenderWindow* window, sf::Font* font, Game* game, int winWidth, int winHeight)
    : Renderer(window, font, 0), game(game), isPlayerTurn(true), 
      windowWidth(winWidth), windowHeight(winHeight) {}

void UIRenderer::render() {
    drawGameTitle();
    drawStatusBar();
}

void UIRenderer::setPlayerTurn(bool isPlayer) {
    isPlayerTurn = isPlayer;
}

void UIRenderer::drawGameTitle() {
    // Background bar
    sf::RectangleShape titleBar(sf::Vector2f(windowWidth, 70.f));
    titleBar.setPosition(0.f, 0.f);
    titleBar.setFillColor(sf::Color(30, 30, 30));
    window->draw(titleBar);
    
    // Game Title
    sf::Text titleText;
    titleText.setFont(*font);
    titleText.setCharacterSize(35);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("CAVE RUN");
    titleText.setPosition(20.f, 18.f);
    window->draw(titleText);
    
    // Turn indicator
    sf::Text currentTurnText;
    currentTurnText.setFont(*font);
    currentTurnText.setCharacterSize(22);
    
    if (isPlayerTurn) {
        currentTurnText.setString("PLAYER'S TURN");
        currentTurnText.setFillColor(sf::Color::Cyan);
    } else {
        currentTurnText.setString("MONSTER'S TURN");
        currentTurnText.setFillColor(sf::Color(255, 100, 100));
    }
    
    sf::FloatRect turnBounds = currentTurnText.getLocalBounds();
    currentTurnText.setPosition(windowWidth / 2.f - turnBounds.width / 2.f, 10.f);
    window->draw(currentTurnText);
    
    // Turn counter
    sf::Text turnCountText;
    turnCountText.setFont(*font);
    turnCountText.setCharacterSize(18);
    turnCountText.setFillColor(sf::Color(200, 200, 200));
    turnCountText.setString("Turn: " + std::to_string(game->getTurnCount()));
    
    sf::FloatRect countBounds = turnCountText.getLocalBounds();
    turnCountText.setPosition(windowWidth / 2.f - countBounds.width / 2.f, 38.f);
    window->draw(turnCountText);
    
    // Difficulty
    sf::Text difficultyText;
    difficultyText.setFont(*font);
    difficultyText.setCharacterSize(18);
    
    sf::Color diffColor;
    switch(game->getDifficulty()) {
        case EASY: diffColor = sf::Color::Green; break;
        case MEDIUM: diffColor = sf::Color::Yellow; break;
        case HARD: diffColor = sf::Color::Red; break;
    }
    
    difficultyText.setFillColor(diffColor);
    difficultyText.setString("(" + game->getDifficultyString() + ")");
    difficultyText.setPosition(windowWidth - 160.f, 10.f);
    window->draw(difficultyText);
    
    // Health
    sf::Text healthText;
    healthText.setFont(*font);
    healthText.setCharacterSize(28);
    
    sf::Color healthColor = game->getPlayer()->getHealth() > 50 ?
                           sf::Color::Green :
                           (game->getPlayer()->getHealth() > 25 ? sf::Color::Yellow : sf::Color::Red);
    
    healthText.setFillColor(healthColor);
    healthText.setString("HP: " + std::to_string(game->getPlayer()->getHealth()));
    healthText.setPosition(windowWidth - 150.f, 32.f);
    window->draw(healthText);
}

void UIRenderer::drawStatusBar() {
    sf::Text text;
    text.setFont(*font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    
    std::string info = "Moves: " + std::to_string(game->getPlayer()->getMovesRemaining()) +
                      " | Poisoned: " + (game->getPlayer()->isPoisoned() ? "YES" : "NO");
    
    text.setString(info);
    text.setPosition(10.f, windowHeight - 30.f);
    window->draw(text);
}
