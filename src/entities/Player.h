#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "../world/Position.h"

class Room;

class Player : public Character {
private:
    int health;
    bool poisoned;
    bool poweredUp;
    double cureChance;  // Probability of curing poison (NOT USED - only healing room cures)
    int poisonDamage;

public:
    Player(Position* startPos, int poisonDmg, double cureChance);
    ~Player() override = default;

    // Override abstract methods from Character
    void sense(Game* game) override;  // Player doesn't need to sense
    Position* getNextMove(Game* game) override;  // GUI handles this
    void update() override;  // Apply poison damage

    // Player-specific methods
    void damage(int amount);
    void heal(int amount);
    void poison();
    void cure();
    void powerUp();
    void visitRoom(Room* room);

    // Getters
    int getHealth() const;
    bool isPoisoned() const;
    bool isDead() const;
    int getMovesRemaining() const;
    void setMovesRemaining(int moves);
};

#endif
