#ifndef ROOM_H
#define ROOM_H

#include "Position.h"
#include <string>
using namespace std;

class Player; // Forward declaration

class Room {
protected:
    Position* position;
    string color;
    string label;
    bool visited;

public:
    Room(Position* pos, string color = "white");
    virtual ~Room();
    
    virtual void visit(Player* player);
    virtual string getRoomType() const;
    
    void setColor(string newColor);
    void setVisited(bool v);
    void setLabel(string newLabel);
    
    Position* getPosition() const;
    string getColor() const;
    string getLabel() const;
    bool isVisited() const;
    
    void display() const;
};

#endif