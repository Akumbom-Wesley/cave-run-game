#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "InputHandler.h"
#include "NotificationManager.h"
#include "GameOverScreen.h"
#include "TurnManager.h"
#include "MoveExecutor.h"
#include "GridRenderer.h"
#include "RoomRenderer.h"
#include "CharacterRenderer.h"
#include "UIRenderer.h"
#include "GameOverHandler.h"

class GameGUI {
private:
    // Core components
    sf::RenderWindow* window;
    sf::Font font;
    Game* game;
    int cellSize;
    int windowWidth;
    int windowHeight;

    // Helper classes
    InputHandler* inputHandler;
    NotificationManager* notificationManager;
    GameOverHandler* gameOverChain;
    GameOverScreen* gameOverScreen;
    TurnManager* turnManager;
    MoveExecutor* moveExecutor;

    // Renderers
    GridRenderer* gridRenderer;
    RoomRenderer* roomRenderer;
    CharacterRenderer* characterRenderer;
    UIRenderer* uiRenderer;

    void setupRenderers();
    void setupGameOverChain();
    void setupHelpers();
    void renderGame();

public:
    GameGUI(Game* game, int cellSize = 50);
    ~GameGUI();

    void run();
    bool isWindowOpen();
};

#endif
