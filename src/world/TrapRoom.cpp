#include "TrapRoom.h"
#include "../entities/Player.h"
#include <iostream>

TrapRoom::TrapRoom(Position* pos, int damage)
    : Room(pos, "white"), damage(damage) {}

void TrapRoom::visit(Player* player) {
    if (!isVisited()) {
        player->damage(damage);
        player->setMovesRemaining(0); // End turn immediately
        setColor("red");
        setVisited(true);
        setLabel("T");
        std::cout << "TRAP! Took " << damage << " damage. Your turn ends!" << std::endl;
    } else {
        std::cout << "Safe - trap already sprung." << std::endl;
    }
}

std::string TrapRoom::getRoomType() const {
    return "Trap";
}
