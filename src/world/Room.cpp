#include "Room.h"
#include <iostream>

Room::Room(Position* pos, string color) 
    : position(pos), color(color), label(" "), visited(false) {}

Room::~Room() {
    delete position; // Now we delete it
}

void Room::visit(Player* player) {
    // Base room does nothing
    if (!visited) {
        visited = true;
    }
}

string Room::getRoomType() const {
    return "Normal";
}

void Room::setColor(string newColor) {
    color = newColor;
}

void Room::setVisited(bool v) {
    visited = v;
}

void Room::setLabel(string newLabel) {
    label = newLabel;
}

Position* Room::getPosition() const {
    return position;
}

string Room::getColor() const {
    return color;
}

string Room::getLabel() const {
    return label;
}

bool Room::isVisited() const {
    return visited;
}

void Room::display() const {
    cout << "[" << label << "]";
}