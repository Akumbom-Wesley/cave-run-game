#include "GameGUI.h"
#include <iostream>

GameGUI::GameGUI(Game* game, int cellSize)
    : game(game), cellSize(cellSize) {

    Map* map = game->getMap();
    windowWidth = (map->getWidth() + 2) * cellSize;
    windowHeight = (map->getHeight() + 4) * cellSize + 80;

    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight),
                                  "Cave Run Game");
    window->setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Warning: Could not load font" << std::endl;
    }

    inputHandler = new InputHandler();
    notificationManager = new NotificationManager(3.0f);

    setupRenderers();
    setupGameOverChain();
    setupHelpers();
}

GameGUI::~GameGUI() {
    delete window;
    delete inputHandler;
    delete notificationManager;
    delete gameOverChain;
    delete gameOverScreen;
    delete turnManager;
    delete moveExecutor;
    delete gridRenderer;
    delete roomRenderer;
    delete characterRenderer;
    delete uiRenderer;
}

void GameGUI::setupRenderers() {
    gridRenderer = new GridRenderer(window, &font, cellSize, game->getMap());
    roomRenderer = new RoomRenderer(window, &font, cellSize, game->getMap());
    characterRenderer = new CharacterRenderer(window, &font, cellSize,
                                             game->getPlayer(), game->getMonster(),
                                             game->getMap());
    uiRenderer = new UIRenderer(window, &font, game, windowWidth, windowHeight);
}

void GameGUI::setupGameOverChain() {
    gameOverChain = new ExitReachedHandler();
    GameOverHandler* collision = new MonsterCollisionHandler();
    GameOverHandler* death = new PlayerDeathHandler();
    gameOverChain->setNext(collision);
    collision->setNext(death);
}

void GameGUI::setupHelpers() {
    gameOverScreen = new GameOverScreen(window, &font, windowWidth, windowHeight, game);
    turnManager = new TurnManager(game, gameOverChain, uiRenderer,
                                  notificationManager, window);

    // Set the render callback so TurnManager can trigger rendering
    turnManager->setRenderCallback([this]() {
        this->renderGame();
    });

    moveExecutor = new MoveExecutor(game, gameOverChain, notificationManager, turnManager);
}

void GameGUI::run() {
    // Main game loop
    while (window->isOpen() && !game->isGameOver()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                InputCommand cmd = inputHandler->processKeyboardState();
                if (cmd.valid) {
                    moveExecutor->executeMove(cmd.dx, cmd.dy);
                }
            }
        }

        renderGame();
    }

    // Show game over screen
    if (game->isGameOver()) {
        renderGame();  // Show final state
        window->display();
        gameOverScreen->show();
    }
}

void GameGUI::renderGame() {
    window->clear(sf::Color(40, 40, 40));

    uiRenderer->render();
    gridRenderer->render();
    roomRenderer->render();
    characterRenderer->render();
    notificationManager->render(window, &font, windowWidth, windowHeight);

    window->display();
}

bool GameGUI::isWindowOpen() {
    return window->isOpen();
}
