#include "../world/PowerUpRoom.h"
#include "../entities/Player.h"
#include <iostream>

PowerUpRoom::PowerUpRoom(Position* pos)
    : Room(pos, "yellow") {}

void PowerUpRoom::visit(Player* player) {
    if (!isVisited()) {  // Use isVisited() method
        // Mark as visited FIRST
        setVisited(true);

        // Give player an extra move IMMEDIATELY
        player->setMovesRemaining(player->getMovesRemaining() + 1);
        std::cout << "Power-up room! +1 extra move this turn!" << std::endl;
    }
}

std::string PowerUpRoom::getRoomType() const {
    return "PowerUp";
}
