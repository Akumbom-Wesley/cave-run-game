#include "../world/HealingRoom.h"
#include "../entities/Player.h"
#include <iostream>

HealingRoom::HealingRoom(Position* pos, int healAmount)
    : Room(pos, "white"), healAmount(healAmount) {}

void HealingRoom::visit(Player* player) {
    if (!isVisited()) {
        // Heal HP
        player->heal(healAmount);

        // CURE poison status
        if (player->isPoisoned()) {
            player->cure();
            std::cout << "Poison cured!" << std::endl;
        }

        setColor("white");
        setVisited(true);
        setLabel("H");
    } else {
        std::cout << "Healing room already used." << std::endl;
    }
}

std::string HealingRoom::getRoomType() const {
    return "Healing";
}
