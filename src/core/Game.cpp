#include "Game.h"
#include "../world/MapGenerator.h"
#include "../core/DifficultyConfig.h"
#include <iostream>
#include <ctime>

Game::Game(int width, int height, Difficulty difficulty)
    : gameOver(false), playerWon(false), turnCount(0), deathCause(NONE), currentDifficulty(difficulty) {

    srand(time(NULL));
    config = DifficultyConfig::getConfig(difficulty);

    map = new Map(width, height);
    // Get difficulty configuration
    DifficultyConfig config = DifficultyConfig::getConfig(difficulty);

    // Create player with difficulty-based poison values
    player = new Player(new Position(1, 1),
                        config.poisonDamagePerTurn,
                        config.poisonCureChance);


    // Use MapGenerator instead of doing it ourselves
    MapGenerator generator(map, config);
    generator.generateMap();
    Position* monsterStart = generator.getMonsterStartPosition();
    monster = new Monster(monsterStart);

    std::cout << "\n=== CAVE RUN GAME STARTED ===\n";
    std::cout << "Difficulty: " << getDifficultyString() << "\n";
    std::cout << "Find the exit at top-right corner!\n";
    std::cout << "P = You, M = Monster, E = Exit\n\n";
}

Game::~Game() {
    delete map;
    delete player;
    delete monster;
}
// Add these to the END of your Game.cpp file

Player* Game::getPlayer() const {
    return player;
}

Monster* Game::getMonster() const {
    return monster;
}

Map* Game::getMap() const {
    return map;
}

Position* Game::getPlayerPosition() const {
    return player->getCurrentRoom();
}

int Game::getMistakeChance() const {
    return config.monsterMistakeChance;
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::hasPlayerWon() const {
    return playerWon;
}

int Game::getTurnCount() const {
    return turnCount;
}

DeathCause Game::getDeathCause() const {
    return deathCause;
}

void Game::setDeathCause(DeathCause cause) {
    deathCause = cause;
}

void Game::incrementTurnCount() {
    turnCount++;
}

Difficulty Game::getDifficulty() const {
    return currentDifficulty;
}

std::string Game::getDifficultyString() const {
    switch(currentDifficulty) {
        case EASY: return "EASY";
        case MEDIUM: return "MEDIUM";
        case HARD: return "HARD";
        default: return "UNKNOWN";
    }
}

void Game::run() {
    while (!gameOver) {
        displayGameState();
        playerTurn();
        if (gameOver) break;
        monsterTurn();
    }

    std::cout << "\n=== GAME OVER ===\n";
    if (playerWon) {
        std::cout << "CONGRATULATIONS! You escaped!\n";
    } else {
        std::cout << "You lost! Better luck next time.\n";
    }

    std::cout << "Turns: " << turnCount << "\n";
    std::cout << "Final Health: " << player->getHealth() << "\n";
}

void Game::checkGameOver() {
    // Check monster collision FIRST
    if (player->getCurrentRoom()->equals(monster->getCurrentRoom())) {
        gameOver = true;
        playerWon = false;
        deathCause = MONSTER_CAUGHT;
        std::cout << "\nThe monster caught you!\n";
        return;
    }

    // Check if reached exit
    if (map->isExitRoom(player->getCurrentRoom())) {
        gameOver = true;
        playerWon = true;
        deathCause = NONE;
        std::cout << "\nYou reached the exit!\n";
        return;
    }

    // Check health depletion
    if (player->isDead()) {
        gameOver = true;
        playerWon = false;
        deathCause = HEALTH_DEPLETED;
        std::cout << "\nYou collapsed from your injuries!\n";
        return;
    }
}

void Game::displayGameState() const {
    map->display(player, monster);
    std::cout << "Health: " << player->getHealth() << " | ";
    std::cout << "Turn: " << turnCount << " | ";
    std::cout << "Poisoned: " << (player->isPoisoned() ? "YES" : "NO") << "\n";
}

void Game::playerTurn() {
    turnCount++;
    player->startTurn(2);

    while (player->canMove() && !gameOver) {
        std::cout << "\nYour turn. Moves left: " << player->getMovesRemaining() << "\n";
        std::cout << "Enter direction (w=up, s=down, a=left, d=right, q=up-left, e=up-right, z=down-left, c=down-right): ";

        char input;
        std::cin >> input;

        int dx = 0, dy = 0;
        switch(input) {
            case 'w': dy = 1; break;
            case 's': dy = -1; break;
            case 'a': dx = -1; break;
            case 'd': dx = 1; break;
            case 'q': dx = -1; dy = 1; break;
            case 'e': dx = 1; dy = 1; break;
            case 'z': dx = -1; dy = -1; break;
            case 'c': dx = 1; dy = -1; break;
            default: std::cout << "Invalid input!\n"; continue;
        }

        Position* current = player->getCurrentRoom();
        int newX = current->getX() + dx;
        int newY = current->getY() + dy;

        if (map->isValidPosition(newX, newY)) {
            delete player->getCurrentRoom();
            Position* newPos = new Position(newX, newY);
            player->setCurrentRoom(newPos);

            Room* room = map->getRoomAt(newPos);
            player->visitRoom(room);
            player->decrementMoves();
            player->update();

            checkGameOver();
        } else {
            std::cout << "Can't move there!\n";
        }
    }
}

void Game::monsterTurn() {
    std::cout << "\n=== MONSTER'S TURN ===\n";
    monster->sense(this);
    Position* newPos = monster->getNextMove(this);

    if (newPos != nullptr) {
        delete monster->getCurrentRoom();
        monster->setCurrentRoom(newPos);
        std::cout << "Monster moved to (" << newPos->getX()
                 << "," << newPos->getY() << ")\n";
    }

    monster->update();
    checkGameOver();
    std::cout << "=== MONSTER TURN ENDED ===\n";
}



