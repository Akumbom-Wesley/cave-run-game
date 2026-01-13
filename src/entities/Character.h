#ifndef CHARACTER_H
#define CHARACTER_H

#include "../world/Position.h"
#include <string>

class Game;
class Map;

class Character {
protected:
    Position* currentRoom;
    int movesRemaining;
    std::string symbol;
    std::string color;

public:
    Character(Position* startPos, std::string symbol, std::string color);
    virtual ~Character();

    // Abstract methods - MUST be implemented by subclasses
    virtual void sense(Game* game) = 0;
    virtual Position* getNextMove(Game* game) = 0;
    virtual void update() = 0;  // NEW: Handle time-based effects

    // Concrete methods
    void move(Map* map);
    void startTurn(int moves);
    bool canMove() const;
    void decrementMoves();

    Position* getCurrentRoom() const;
    void setCurrentRoom(Position* pos);
    std::string getSymbol() const;
    std::string getColor() const;
};

#endif
