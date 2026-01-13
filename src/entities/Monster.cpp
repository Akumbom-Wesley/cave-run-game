#include "../entities/Monster.h"
#include "../core/Game.h"
#include "../world/Map.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

Monster::Monster(Position* startPos)
    : Character(startPos, "M", "red"), playerLastKnownPosition(nullptr) {}

Monster::~Monster() {
    if (playerLastKnownPosition) {
        delete playerLastKnownPosition;
    }
}

void Monster::sense(Game* game) {
    // Monster senses player's position
    Position* playerPos = game->getPlayerPosition();

    if (playerLastKnownPosition) {
        delete playerLastKnownPosition;
    }

    playerLastKnownPosition = new Position(playerPos->getX(), playerPos->getY());
}

Position* Monster::getNextMove(Game* game) {
    Map* map = game->getMap();
    Position* playerPos = game->getPlayerPosition();

    // Get mistake chance based on difficulty
    int mistakeChance = game->getMistakeChance();

    // Monster makes a mistake (random move)
    int roll = rand() % 100;
    if (roll < mistakeChance) {
        std::cout << "Monster confused! Moving randomly..." << std::endl;
        return getRandomMove(map);
    }

    // Calculate distances
    int distanceToPlayer = abs(currentRoom->getX() - playerPos->getX()) +
                          abs(currentRoom->getY() - playerPos->getY());

    Position* exitPos = map->getExitPosition();
    int monsterToExit = abs(currentRoom->getX() - exitPos->getX()) +
                       abs(currentRoom->getY() - exitPos->getY());
    int playerToExit = abs(playerPos->getX() - exitPos->getX()) +
                      abs(playerPos->getY() - exitPos->getY());

    Position* targetPos;

    // Strategy based on distances
    if (distanceToPlayer <= 3) {
        // Player is close - chase directly
        targetPos = playerPos;
        std::cout << "Monster CHASING player (close range)!" << std::endl;
    }
    else if (monsterToExit < playerToExit && playerToExit < 5) {
        // Monster closer to exit AND player is approaching - block exit
        targetPos = exitPos;
        std::cout << "Monster BLOCKING exit!" << std::endl;
    }
    else {
        // Default: move towards player
        targetPos = playerPos;
        std::cout << "Monster pursuing player..." << std::endl;
    }

    return moveTowardsTarget(targetPos, map);
}

void Monster::update() {
    // Monster doesn't have time-based effects
}

Position* Monster::moveTowardsTarget(Position* target, Map* map) {
    int dx = 0, dy = 0;

    // Calculate direction to target
    if (target->getX() > currentRoom->getX()) dx = 1;
    else if (target->getX() < currentRoom->getX()) dx = -1;

    if (target->getY() > currentRoom->getY()) dy = 1;
    else if (target->getY() < currentRoom->getY()) dy = -1;

    int newX = currentRoom->getX() + dx;
    int newY = currentRoom->getY() + dy;

    // Validate the move
    if (map->isValidPosition(newX, newY)) {
        return new Position(newX, newY);
    }

    // If diagonal move fails, try horizontal or vertical only
    if (dx != 0 && map->isValidPosition(currentRoom->getX() + dx, currentRoom->getY())) {
        return new Position(currentRoom->getX() + dx, currentRoom->getY());
    }

    if (dy != 0 && map->isValidPosition(currentRoom->getX(), currentRoom->getY() + dy)) {
        return new Position(currentRoom->getX(), currentRoom->getY() + dy);
    }

    // If all moves fail, stay in place
    return new Position(currentRoom->getX(), currentRoom->getY());
}

Position* Monster::getRandomMove(Map* map) {
    // Generate random direction
    int dx = (rand() % 3) - 1;  // -1, 0, or 1
    int dy = (rand() % 3) - 1;  // -1, 0, or 1

    int newX = currentRoom->getX() + dx;
    int newY = currentRoom->getY() + dy;

    if (map->isValidPosition(newX, newY)) {
        return new Position(newX, newY);
    }

    // If invalid, stay in place
    return new Position(currentRoom->getX(), currentRoom->getY());
}

int Monster::distanceToExit(Map* map) {
    Position* exit = map->getExitPosition();
    return abs(currentRoom->getX() - exit->getX()) +
           abs(currentRoom->getY() - exit->getY());
}

int Monster::distanceToPlayer(Position* playerPos) {
    return abs(currentRoom->getX() - playerPos->getX()) +
           abs(currentRoom->getY() - playerPos->getY());
}
