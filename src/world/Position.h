#ifndef POSITION_H
#define POSITION_H

#include <string>
using namespace std;

class Position {
private:
    int x;
    int y;

public:
    Position(int x, int y);
    
    int getX() const;
    int getY() const;
    void setX(int newX);
    void setY(int newY);
    
    bool equals(Position* other) const;
    int distanceTo(Position* other) const;
    string toString() const;
};

#endif