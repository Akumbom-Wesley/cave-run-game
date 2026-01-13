#include "Character.h"

Character::Character(Position* startPos, std::string symbol, std::string color)
    : currentRoom(startPos), movesRemaining(0), symbol(symbol), color(color) {}

Character::~Character() {
    delete currentRoom;
}

void Character::startTurn(int moves) {
    movesRemaining = moves;
}

bool Character::canMove() const {
    return movesRemaining > 0;
}

void Character::decrementMoves() {
    if (movesRemaining > 0) {
        movesRemaining--;
    }
}

Position* Character::getCurrentRoom() const {
    return currentRoom;
}

void Character::setCurrentRoom(Position* pos) {
    currentRoom = pos;
}

std::string Character::getSymbol() const {
    return symbol;
}

std::string Character::getColor() const {
    return color;
}
