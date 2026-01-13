#include "../world/Position.h"
#include <cmath>
#include <sstream>

Position::Position(int x, int y) : x(x), y(y) {}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

void Position::setX(int newX) {
    x = newX;
}

void Position::setY(int newY) {
    y = newY;
}

bool Position::equals(Position* other) const {
    if (other == nullptr) return false;
    return (x == other->x && y == other->y);
}

int Position::distanceTo(Position* other) const {
    if (other == nullptr) return 9999;
    return abs(x - other->x) + abs(y - other->y);
}

string Position::toString() const {
    stringstream ss;
    ss << "(" << x << "," << y << ")";
    return ss.str();
}