#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include "Game.h"
#include "GameOverHandler.h"
#include "UIRenderer.h"
#include "NotificationManager.h"
#include <SFML/Graphics.hpp>
#include <functional>

class TurnManager {
private:
    Game* game;
    GameOverHandler* gameOverChain;
    UIRenderer* uiRenderer;
    NotificationManager* notificationManager;
    sf::RenderWindow* window;
    bool isPlayerTurn;
    std::function<void()> renderCallback;

public:
    TurnManager(Game* game, GameOverHandler* chain, UIRenderer* uiRenderer,
                NotificationManager* notifManager, sf::RenderWindow* window);
    ~TurnManager();

    void handleEndOfPlayerTurn();
    bool getIsPlayerTurn() const;
    void setIsPlayerTurn(bool value);
    void setRenderCallback(std::function<void()> callback);
};

#endif
