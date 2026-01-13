#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include "../world/Position.h"

class Game;
class Map;

class Monster : public Character {
private:
    Position* playerLastKnownPosition;

public:
    Monster(Position* startPos);
    ~Monster() override;

    // Override abstract methods from Character
    void sense(Game* game) override;
    Position* getNextMove(Game* game) override;
    void update() override;

    // Monster-specific methods
    Position* moveTowardsTarget(Position* target, Map* map);
    Position* getRandomMove(Map* map);  // NEW: For mistake behavior
    int distanceToExit(Map* map);
    int distanceToPlayer(Position* playerPos);
};

#endif
