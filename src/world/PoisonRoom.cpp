#include "PoisonRoom.h"
#include "../entities/Player.h"
#include <iostream>

PoisonRoom::PoisonRoom(Position* pos) : Room(pos, "white") {}

void PoisonRoom::visit(Player* player) {
    if (!isVisited()) {
        setColor("green");
        setVisited(true);
        setLabel("P");

        // ONLY apply poison status - NO immediate damage
        if (!player->isPoisoned()) {
            player->poison();
            std::cout << "Poisoned! You'll lose HP after each move until cured!" << std::endl;
        }
    }
}

std::string PoisonRoom::getRoomType() const {
    return "Poison";
}
