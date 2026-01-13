#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include "Position.h"
class Player;
class Monster;

class Map {
private:
    int width;
    int height;
    Room*** grid;
    Position* exitPosition;

public:
    Map(int width, int height);
    ~Map();
    
    void addRoom(Room* room);
    Room* getRoomAt(Position* pos) const;
    Room* getRoomAt(int x, int y) const;
    
    bool isValidPosition(Position* pos) const;
    bool isValidPosition(int x, int y) const;
    
    void setExitPosition(Position* pos);
    Position* getExitPosition() const;
    bool isExitRoom(Position* pos) const;
    
    int getWidth() const;
    int getHeight() const;
    
    void display(Player* player, Monster* monster) const;
};

#endif