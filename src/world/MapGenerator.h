#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "Map.h"
#include "Position.h"
#include "../core/DifficultyConfig.h"
#include <vector>

class MapGenerator {
private:
    Map* map;
    DifficultyConfig config;

    std::vector<Position*> calculateSafePath();
    void placeHazards(const std::vector<Position*>& safePath);
    void placeHelpfulRooms();
    Position* calculateMonsterStartPosition(const std::vector<Position*>& safePath);

public:
    MapGenerator(Map* map, DifficultyConfig config);
    ~MapGenerator();

    void generateMap();
    Position* getMonsterStartPosition();
};

#endif
