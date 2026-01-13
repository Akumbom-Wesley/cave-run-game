#include "../entities/Player.h"
#include "../world/Room.h"
#include <iostream>
#include <cstdlib>

Player::Player(Position* startPos, int poisonDmg, double cureChance)
    : Character(startPos, "P", "blue"),
    health(100), poisoned(false), poweredUp(false),
    cureChance(cureChance),      // ← Use passed value
    poisonDamage(poisonDmg) {    // ← Use passed value
    startTurn(2);
}


void Player::sense(Game* game) {
    // Player doesn't need to sense - user controls movement
    // This method exists to satisfy Character interface
}

Position* Player::getNextMove(Game* game) {
    // Movement is handled by GUI input
    // This method exists to satisfy Character interface
    return nullptr;
}

void Player::update() {
    // Apply poison damage
    if (poisoned) {
        damage(poisonDamage);
        std::cout << "Poison damage: -" << poisonDamage << " HP!" << std::endl;

        // Try to randomly cure poison
        int roll = rand() % 100;
        if (roll < (cureChance * 100)) {
            cure();
            std::cout << "Your body fought off the poison!" << std::endl;
        }
    }
}

void Player::damage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    std::cout << "Took " << amount << " damage! HP: " << health << std::endl;
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) health = 100;
    std::cout << "Healed " << amount << " HP! HP: " << health << std::endl;
}

void Player::poison() {
    if (!poisoned) {
        poisoned = true;
        std::cout << "POISONED! You'll lose HP after each move!" << std::endl;
    }
}

void Player::cure() {
    if (poisoned) {
        poisoned = false;
        std::cout << "Poison CURED!" << std::endl;
    }
}

void Player::powerUp() {
    poweredUp = true;
    // Add extra move immediately
    movesRemaining++;
    std::cout << "POWER UP! +1 extra move!" << std::endl;
}

void Player::visitRoom(Room* room) {
    if (room != nullptr) {
        room->visit(this);
    }
}

int Player::getHealth() const {
    return health;
}

bool Player::isPoisoned() const {
    return poisoned;
}

bool Player::isDead() const {
    return health <= 0;
}

int Player::getMovesRemaining() const {
    return movesRemaining;
}

void Player::setMovesRemaining(int moves) {
    movesRemaining = moves;
}
