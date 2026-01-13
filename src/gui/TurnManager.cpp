#include "TurnManager.h"

TurnManager::TurnManager(Game* game, GameOverHandler* chain, 
                         UIRenderer* uiRenderer, NotificationManager* notifManager,
                         sf::RenderWindow* window)
    : game(game), gameOverChain(chain), uiRenderer(uiRenderer),
      notificationManager(notifManager), window(window), isPlayerTurn(true) {}

TurnManager::~TurnManager() {}

void TurnManager::handleEndOfPlayerTurn() {
    notificationManager->hide();
    game->incrementTurnCount();
    isPlayerTurn = false;
    uiRenderer->setPlayerTurn(false);
    
    // Render the game state after player's turn
    if (renderCallback) {
        renderCallback();
    }

    // Wait before monster moves (so player can see their final position)
    sf::sleep(sf::seconds(1.5));

    // Monster takes turn
    game->monsterTurn();

    // Render again to show monster's new position
    if (renderCallback) {
        renderCallback();
    }

    // Check game over after monster move
    if (gameOverChain->handle(game)) {
        return;
    }

    // Brief pause before starting next player turn
    sf::sleep(sf::seconds(0.5));

    // Start new player turn
    isPlayerTurn = true;
    uiRenderer->setPlayerTurn(true);
    game->getPlayer()->startTurn(2);
}

bool TurnManager::getIsPlayerTurn() const {
    return isPlayerTurn;
}

void TurnManager::setIsPlayerTurn(bool value) {
    isPlayerTurn = value;
}

void TurnManager::setRenderCallback(std::function<void()> callback) {
    renderCallback = callback;
}
