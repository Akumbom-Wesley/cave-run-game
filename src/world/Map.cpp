#include "../world/Map.h"
#include "../entities/Player.h"
#include "../entities/Monster.h"
#include <iostream>

Map::Map(int width, int height)
    : width(width), height(height), exitPosition(nullptr) {

    // Allocate 2D array
    grid = new Room**[width + 1];
    for (int i = 0; i <= width; i++) {
        grid[i] = new Room*[height + 1];
        for (int j = 0; j <= height; j++) {
            grid[i][j] = nullptr;
        }
    }
}

Map::~Map() {
    // Delete all rooms first
    for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= height; j++) {
            if (grid[i][j] != nullptr) {
                delete grid[i][j];
                grid[i][j] = nullptr;
            }
        }
    }

    // Delete grid arrays
    for (int i = 0; i <= width; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    // Don't delete exitPosition - it's just a pointer to existing Position
    // delete exitPosition;
}

void Map::addRoom(Room* room) {
    Position* pos = room->getPosition();
    if (isValidPosition(pos)) {
        int x = pos->getX();
        int y = pos->getY();

        // Delete old room if exists
        if (grid[x][y] != nullptr) {
            delete grid[x][y];
        }

        grid[x][y] = room;
    }
}

Room* Map::getRoomAt(Position* pos) const {
    if (pos == nullptr || !isValidPosition(pos)) {
        return nullptr;
    }
    return grid[pos->getX()][pos->getY()];
}

Room* Map::getRoomAt(int x, int y) const {
    if (!isValidPosition(x, y)) {
        return nullptr;
    }
    return grid[x][y];
}

bool Map::isValidPosition(Position* pos) const {
    if (pos == nullptr) return false;
    return isValidPosition(pos->getX(), pos->getY());
}

bool Map::isValidPosition(int x, int y) const {
    return (x >= 1 && x <= width && y >= 1 && y <= height);
}

void Map::setExitPosition(Position* pos) {
    exitPosition = pos;
}

Position* Map::getExitPosition() const {
    return exitPosition;
}

bool Map::isExitRoom(Position* pos) const {
    if (exitPosition == nullptr || pos == nullptr) return false;
    return exitPosition->equals(pos);
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

void Map::display(Player* player, Monster* monster) const {
    cout << "\n=== MAP ===\n";

    for (int y = height; y >= 1; y--) {
        for (int x = 1; x <= width; x++) {
            Position* pos = new Position(x, y);

            if (player->getCurrentRoom()->equals(pos)) {
                cout << "[P]";
            } else if (monster->getCurrentRoom()->equals(pos)) {
                cout << "[M]";
            } else if (isExitRoom(pos)) {
                cout << "[E]";
            } else {
                Room* room = getRoomAt(pos);
                if (room != nullptr && room->isVisited()) {
                    cout << "[" << room->getLabel() << "]";
                } else {
                    cout << "[ ]";
                }
            }

            delete pos;
        }
        cout << "\n";
    }
    cout << "===========\n";
}