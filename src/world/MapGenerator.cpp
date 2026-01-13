#include "../world/MapGenerator.h"
#include "Room.h"
#include "PoisonRoom.h"
#include "TrapRoom.h"
#include "HealingRoom.h"
#include "PowerUpRoom.h"
#include <algorithm>
#include <set>

MapGenerator::MapGenerator(Map* map, DifficultyConfig config)
    : map(map), config(config) {}

MapGenerator::~MapGenerator() {}

void MapGenerator::generateMap() {
    // Step 1: Create all normal rooms
    for (int x = 1; x <= map->getWidth(); x++) {
        for (int y = 1; y <= map->getHeight(); y++) {
            Position* pos = new Position(x, y);
            map->addRoom(new Room(pos, "white"));
        }
    }
    
    // Step 2: Set exit
    map->setExitPosition(new Position(map->getWidth(), map->getHeight()));
    
    // Step 3: Calculate safe path
    std::vector<Position*> safePath = calculateSafePath();
    
    // Step 4: Place hazards
    placeHazards(safePath);
    
    // Step 5: Place helpful rooms
    placeHelpfulRooms();
    
    // Cleanup
    for (Position* pos : safePath) {
        delete pos;
    }
}

std::vector<Position*> MapGenerator::calculateSafePath() {
    std::vector<Position*> path;
    Position* start = new Position(1, 1);
    Position* exit = map->getExitPosition();
    
    int currentX = start->getX();
    int currentY = start->getY();
    
    // Move right
    while (currentX < exit->getX()) {
        path.push_back(new Position(currentX, currentY));
        currentX++;
    }
    
    // Move up
    while (currentY <= exit->getY()) {
        path.push_back(new Position(currentX, currentY));
        currentY++;
    }
    
    delete start;
    return path;
}

void MapGenerator::placeHazards(const std::vector<Position*>& safePath) {
    std::set<std::string> safePositions;
    for (Position* pos : safePath) {
        safePositions.insert(pos->toString());
    }
    
    int totalRooms = map->getWidth() * map->getHeight();
    int poisonCount = (totalRooms * config.poisonPercentage) / 100;
    int trapCount = (totalRooms * config.trapPercentage) / 100;
    
    std::vector<Position*> availablePositions;
    for (int x = 1; x <= map->getWidth(); x++) {
        for (int y = 1; y <= map->getHeight(); y++) {
            Position temp(x, y);
            if (safePositions.find(temp.toString()) == safePositions.end() &&
                !(x == 1 && y == 1) &&
                !(x == map->getWidth() && y == map->getHeight())) {
                availablePositions.push_back(new Position(x, y));
            }
        }
    }
    
    std::random_shuffle(availablePositions.begin(), availablePositions.end());
    
    int index = 0;
    // Place poison rooms
    for (int i = 0; i < poisonCount && index < availablePositions.size(); i++, index++) {
        Position* pos = availablePositions[index];
        map->addRoom(new PoisonRoom(new Position(pos->getX(), pos->getY())));
    }
    
    // Place trap rooms
    for (int i = 0; i < trapCount && index < availablePositions.size(); i++, index++) {
        Position* pos = availablePositions[index];
        map->addRoom(new TrapRoom(new Position(pos->getX(), pos->getY()), config.trapDamage));
    }
    
    for (Position* pos : availablePositions) {
        delete pos;
    }
}

void MapGenerator::placeHelpfulRooms() {
    int totalRooms = map->getWidth() * map->getHeight();
    int healingCount = (totalRooms * config.healingPercentage) / 100;
    int powerUpCount = (totalRooms * config.powerUpPercentage) / 100;
    
    std::vector<Position*> normalRooms;
    for (int x = 1; x <= map->getWidth(); x++) {
        for (int y = 1; y <= map->getHeight(); y++) {
            Room* room = map->getRoomAt(x, y);
            if (room != nullptr && room->getRoomType() == "Normal" &&
                !(x == 1 && y == 1) &&
                !(x == map->getWidth() && y == map->getHeight())) {
                normalRooms.push_back(new Position(x, y));
            }
        }
    }
    
    std::random_shuffle(normalRooms.begin(), normalRooms.end());
    
    int index = 0;
    for (int i = 0; i < healingCount && index < normalRooms.size(); i++, index++) {
        Position* pos = normalRooms[index];
        map->addRoom(new HealingRoom(new Position(pos->getX(), pos->getY()), config.healAmount));
    }
    
    for (int i = 0; i < powerUpCount && index < normalRooms.size(); i++, index++) {
        Position* pos = normalRooms[index];
        map->addRoom(new PowerUpRoom(new Position(pos->getX(), pos->getY())));
    }
    
    for (Position* pos : normalRooms) {
        delete pos;
    }
}

Position* MapGenerator::calculateMonsterStartPosition(const std::vector<Position*>& safePath) {
    int requiredDistance = config.monsterStartDistance;
    Position* playerStart = new Position(1, 1);
    
    for (int x = map->getWidth(); x >= 1; x--) {
        for (int y = map->getHeight(); y >= 1; y--) {
            Position* pos = new Position(x, y);
            int distToPlayer = pos->distanceTo(playerStart);
            
            if (distToPlayer >= requiredDistance &&
                !(x == 1 && y == 1) &&
                !(x == map->getWidth() && y == map->getHeight())) {
                delete playerStart;
                return pos;
            }
            delete pos;
        }
    }
    
    delete playerStart;
    return new Position(map->getWidth() / 2, map->getHeight() / 2);
}

Position* MapGenerator::getMonsterStartPosition() {
    std::vector<Position*> safePath = calculateSafePath();
    Position* monsterPos = calculateMonsterStartPosition(safePath);
    
    for (Position* pos : safePath) {
        delete pos;
    }
    
    return monsterPos;
}
